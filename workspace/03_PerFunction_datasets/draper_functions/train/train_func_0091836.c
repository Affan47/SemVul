getPeerAddr() const
{
    union
    {
      struct sockaddr_storage storage;
      struct sockaddr         sa;
      struct sockaddr_in      sa_in;
      struct sockaddr_in6     sa_in6;
      struct in_addr          addr;
    } addr;

    addr.storage = _peeraddr;

    std::string ret;
    formatIp(addr.sa_in, ret);
    return ret;
}
