SendTo(const void* data, size_t size,
                     const talk_base::SocketAddress& addr, bool payload) {
  int sent = socket_->SendTo(data, size, addr);
  if (sent < 0) {
    error_ = socket_->GetError();
    LOG_J(LS_ERROR, this) << "UDP send of " << size
                          << " bytes failed with error " << error_;
  }
  return sent;
}
