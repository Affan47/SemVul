OnReadPacket(
    const char* data, size_t size,
    const talk_base::SocketAddress& remote_addr) {
  if (Connection* conn = GetConnection(remote_addr)) {
    conn->OnReadPacket(data, size);
  } else {
    Port::OnReadPacket(data, size, remote_addr);
  }
}
