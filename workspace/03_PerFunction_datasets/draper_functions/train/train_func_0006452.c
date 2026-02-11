OnConnectEvent(AsyncSocket* socket) {

    ASSERT(socket == socket_);
    if (server_addr_.IsAny()) {
      connected_ = true;
      SignalConnectEvent(this);
    } else {
      SendConnectRequest();
    }
  }
