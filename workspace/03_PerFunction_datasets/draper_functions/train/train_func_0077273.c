matchAddr(const char* ipv6)
  {
    LibcWrapper::AddrInfo_var ai(LibcWrapper::getAddrInfo(ipv6,0));
    if (!ai.in()) return 0;

    sockaddr_in6* sa = (sockaddr_in6*)ai->addr();
    CORBA::Octet* ip6_bytes = (CORBA::Octet*)&sa->sin6_addr.s6_addr;

    CORBA::ULong bits = prefix_;
    CORBA::ULong i;

    for (i=0; i < 16 && bits > 7; ++i, bits-=8) {
      if (network_[i] != ip6_bytes[i])
	return 0;
    }
    if (bits) {
      CORBA::Octet mask = (0xff << (8 - bits)) & 0xff;
      if ((network_[i] & mask) != (ip6_bytes[i] & mask))
	return 0;
    }
    return 1;
  }
