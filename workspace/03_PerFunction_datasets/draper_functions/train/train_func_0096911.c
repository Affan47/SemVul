Create(Object* value) {
  isolate_->counters()->global_handles()->Increment();
  if (first_free_ == NULL) {
    first_block_ = new NodeBlock(first_block_);
    first_block_->PutNodesOnFreeList(&first_free_);
  }
  ASSERT(first_free_ != NULL);

  Node* result = first_free_;
  first_free_ = result->next_free();
  result->Acquire(value, this);
  if (isolate_->heap()->InNewSpace(value) &&
      !result->is_in_new_space_list()) {
    new_space_nodes_.Add(result);
    result->set_in_new_space_list(true);
  }
  return result->handle();
}
