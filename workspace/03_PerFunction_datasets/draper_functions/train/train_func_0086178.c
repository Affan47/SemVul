SendTcp(const void* pv, size_t cb) {
    size_t capacity = server_->send_buffer_capacity_ - send_buffer_.size();
    if (0 == capacity) {
      write_enabled_ = true;
      error_ = EWOULDBLOCK;
      return -1;
    }
    size_t consumed = _min(cb, capacity);
    const char* cpv = static_cast<const char*>(pv);
    send_buffer_.insert(send_buffer_.end(), cpv, cpv + consumed);
    server_->SendTcp(this);
    return static_cast<int>(consumed);
  }
