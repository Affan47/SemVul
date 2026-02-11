EstimateMTU(uint16* mtu) {
    SocketAddress addr = GetRemoteAddress();
    if (addr.IsAny()) {
      error_ = ENOTCONN;
      return -1;
    }

#if defined(WIN32)

    WinPing ping;
    if (!ping.IsValid()) {
      error_ = EINVAL;
      return -1;
    }

    for (int level = 0; PACKET_MAXIMUMS[level + 1] > 0; ++level) {
      int32 size = PACKET_MAXIMUMS[level] - IP_HEADER_SIZE - ICMP_HEADER_SIZE;
      WinPing::PingResult result = ping.Ping(addr.ip(), size, 0, 1, false);
      if (result == WinPing::PING_FAIL) {
        error_ = EINVAL;
        return -1;
      } else if (result != WinPing::PING_TOO_LARGE) {
        *mtu = PACKET_MAXIMUMS[level];
        return 0;
      }
    }

    ASSERT(false);
    return -1;
#elif defined(IOS) || defined(OSX)


    error_ = EINVAL;
    return -1;
#elif defined(LINUX) || defined(ANDROID)

    int value;
    socklen_t vlen = sizeof(value);
    int err = getsockopt(s_, IPPROTO_IP, IP_MTU, &value, &vlen);
    if (err < 0) {
      UpdateLastError();
      return err;
    }

    ASSERT((0 <= value) && (value <= 65536));
    *mtu = value;
    return 0;
#endif
  }
