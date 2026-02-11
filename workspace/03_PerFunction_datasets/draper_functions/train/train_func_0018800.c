VP8LRefsCursorNextBlock(VP8LRefsCursor* const c) {
  PixOrCopyBlock* const b = c->cur_block_->next_;
  c->cur_pos = (b == NULL) ? NULL : b->start_;
  c->last_pos_ = (b == NULL) ? NULL : b->start_ + b->size_;
  c->cur_block_ = b;
}
