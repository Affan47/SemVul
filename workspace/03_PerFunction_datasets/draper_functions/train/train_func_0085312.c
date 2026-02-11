SendPacket(const char* data, size_t len) {

  return (impl_) ? impl_->SendPacket(data, len) : -1;
}
