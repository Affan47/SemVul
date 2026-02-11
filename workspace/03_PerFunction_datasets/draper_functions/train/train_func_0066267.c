BackUpInputToCurrentPosition() {
  int backup_bytes = buffer_size_ + buffer_size_after_limit_ + overflow_bytes_;
  if (backup_bytes > 0) {
    input_->BackUp(backup_bytes);


    total_bytes_read_ -= buffer_size_ + buffer_size_after_limit_;
    buffer_size_ = 0;
    buffer_size_after_limit_ = 0;
    overflow_bytes_ = 0;
  }
}
