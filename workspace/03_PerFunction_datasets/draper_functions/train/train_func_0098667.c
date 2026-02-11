AllocNewBlock(const size_t block_size) {
  AllocatedBlock *block;

  if ( blocks_alloced_ < arraysize(first_blocks_) ) {

    block = &first_blocks_[blocks_alloced_++];
  } else {
    if (overflow_blocks_ == NULL) overflow_blocks_ = new vector<AllocatedBlock>;

    overflow_blocks_->resize(overflow_blocks_->size()+1);

    block = &overflow_blocks_->back();
  }

  block->mem = reinterpret_cast<char*>(malloc(block_size));
  block->size = block_size;

  return block;
}
