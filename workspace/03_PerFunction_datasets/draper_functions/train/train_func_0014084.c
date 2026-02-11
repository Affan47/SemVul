Next(void** data, int* size) {
  if (position_ < size_) {
    last_returned_size_ = min(block_size_, size_ - position_);
    *data = data_ + position_;
    *size = last_returned_size_;
    position_ += last_returned_size_;
    return true;
  } else {

    last_returned_size_ = 0;
    return false;
  }
}
