GetExternalConnection(
    const talk_base::SocketAddress& ext_addr) {
  for (size_t i = 0; i < external_connections_.size(); ++i) {
    if (ext_addr == external_connections_[i]->addr_pair().source())
      return external_connections_[i];
  }
  return 0;
}
