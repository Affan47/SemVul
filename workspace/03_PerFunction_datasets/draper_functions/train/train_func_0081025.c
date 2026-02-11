GetAddress(SocketAddress* address) const {
  *address = listener_->GetLocalAddress();
  return !address->IsNil();
}
