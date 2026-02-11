Append(const char c) {
  if (pos_ < Log::kMessageBufferSize) {
    log_->message_buffer_[pos_++] = c;
  }
  ASSERT(pos_ <= Log::kMessageBufferSize);
}
