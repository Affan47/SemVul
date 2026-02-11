Bind(const SocketAddress& addr) {
    if (!local_addr_.IsAny()) {
      error_ = EINVAL;
      return -1;
    }
    local_addr_ = addr;
    int result = server_->Bind(this, &local_addr_);
    if (result != 0) {
      local_addr_.Clear();
      error_ = EADDRINUSE;
    } else {
      bound_ = true;
      was_any_ = addr.IsAnyIP();
    }
    return result;
  }
