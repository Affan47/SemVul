OnConnectEvent(AsyncSocket * socket) {
  std::string probe;

  switch (TEST_ORDER[next_]) {
    case PROXY_HTTPS:
      probe.assign("CONNECT www.google.com:443 HTTP/1.0\r\n"
                   "User-Agent: ");
      probe.append(agent_);
      probe.append("\r\n"
                   "Host: www.google.com\r\n"
                   "Content-Length: 0\r\n"
                   "Proxy-Connection: Keep-Alive\r\n"
                   "\r\n");
      break;
    case PROXY_SOCKS5:
      probe.assign("\005\001\000", 3);
      break;
    default:
      ASSERT(false);
      return;
  }

  LOG(LS_VERBOSE) << "AutoDetectProxy probing type " << TEST_ORDER[next_]
                  << " sending " << probe.size() << " bytes";
  socket_->Send(probe.data(), probe.size());
}
