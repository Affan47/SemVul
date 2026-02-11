WriteOffsetLocked(const void* buffer,
                                           size_t bytes,
                                           size_t offset,
                                           size_t* bytes_written) {
  if (state_ == SS_CLOSED) {
    return SR_EOS;
  }

  if (data_length_ + offset >= buffer_length_) {
    return SR_BLOCK;
  }

  const size_t available = buffer_length_ - data_length_ - offset;
  const size_t write_position = (read_position_ + data_length_ + offset)
      % buffer_length_;
  const size_t copy = _min(bytes, available);
  const size_t tail_copy = _min(copy, buffer_length_ - write_position);
  const char* const p = static_cast<const char*>(buffer);
  memcpy(&buffer_[write_position], p, tail_copy);
  memcpy(&buffer_[0], p + tail_copy, copy - tail_copy);

  if (bytes_written) {
    *bytes_written = copy;
  }
  return SR_SUCCESS;
}
