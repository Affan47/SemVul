Connect(const talk_base::SocketAddress& addr) {
  if (cricket_socket_->Connect(addr) < 0) {
    return cricket_socket_->IsBlocking();
  }
  return true;
}
