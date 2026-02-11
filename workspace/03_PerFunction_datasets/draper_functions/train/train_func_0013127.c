Connect(const SocketAddress& addr) {
    if (type_ == SOCK_STREAM) {
      if (!server_->Check(FP_TCP, GetLocalAddress(), addr)) {
        LOG(LS_VERBOSE) << "FirewallSocket outbound TCP connection from "
                        << GetLocalAddress().ToString() << " to "
                        << addr.ToString() << " denied";

        SetError(EHOSTUNREACH);
        return SOCKET_ERROR;
      }
    }
    return AsyncSocketAdapter::Connect(addr);
  }
