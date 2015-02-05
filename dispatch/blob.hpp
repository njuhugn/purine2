// Copyright Lin Min 2015
#ifndef PURINE_BLOB
#define PURINE_BLOB

#include <memory>

#include "dispatch/node.hpp"
#include "operations/operation.hpp"
#include "operations/tensor.hpp"

namespace purine {

using std::shared_ptr;

class Op_;

class Blob : public Node {
  friend Op_& operator >> (const vector<Blob*>& inputs, Op_& op);
  friend const vector<Blob*>& operator >> (Op_& op,
      const vector<Blob*>& outputs);
 protected:
  shared_ptr<Tensor> tensor_;
  cudaEvent_t cuda_event_ = NULL;
 public:
  explicit Blob(int rank, int device, const Size& size);
  explicit Blob(shared_ptr<Tensor> tensor);
  virtual ~Blob() override;

  inline cudaEvent_t cuda_event() { return cuda_event_; }
  inline Tensor* tensor() { return tensor_.get(); }
  inline shared_ptr<Tensor> shared_tensor() { return tensor_; }

  virtual void compute() override;
};

}

#endif
