GetReadData(size_t* size) {
  CritScope cs(&crit_);
  *size = (read_position_ + data_length_ <= buffer_length_) ?
      data_length_ : buffer_length_ - read_position_;
  return &buffer_[read_position_];
}
