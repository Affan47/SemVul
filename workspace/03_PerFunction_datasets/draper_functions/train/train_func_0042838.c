AddressInUseMsg(const std::string& ipaddr, unsigned short int port)
  {
    std::ostringstream msg;
    msg << "address " << ipaddr << ':' << port << " in use";
    return msg.str();
  }
}
