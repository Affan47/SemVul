OnSendPacket(const void* data, size_t size,
                                   StunRequest* req) {
  int sent = socket_->SendTo(data, size, GetAddress());
  if (sent <= 0) {
    LOG(LS_VERBOSE) << "OnSendPacket: failed sending to " << GetAddress() <<
        std::strerror(socket_->GetError());
    ASSERT(sent < 0);
  }
}
