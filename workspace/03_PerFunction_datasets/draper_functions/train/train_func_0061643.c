OnRemoteAddress(
    const talk_base::SocketAddress& remote_address) {
  remote_address_ = remote_address;
  set_readable(true);

  if (port_ != NULL)
    SetWritable();
}
