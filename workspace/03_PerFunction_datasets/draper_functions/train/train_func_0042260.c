tor_addr_parse_PTR_name(tor_addr_t *result, const char *address,
                                   int family, int accept_regular)
{
  if (!strcasecmpend(address, ".in-addr.arpa")) {

    char buf[INET_NTOA_BUF_LEN];
    size_t len;
    struct in_addr inaddr;
    if (family == AF_INET6)
      return -1;

    len = strlen(address) - strlen(".in-addr.arpa");
    if (len >= INET_NTOA_BUF_LEN)
      return -1;

    memcpy(buf, address, len);
    buf[len] = '\0';
    if (tor_inet_aton(buf, &inaddr) == 0)
      return -1;


    inaddr.s_addr = (uint32_t)
      (((inaddr.s_addr & 0x000000ff) << 24)
       |((inaddr.s_addr & 0x0000ff00) << 8)
       |((inaddr.s_addr & 0x00ff0000) >> 8)
       |((inaddr.s_addr & 0xff000000) >> 24));

    if (result) {
      tor_addr_from_in(result, &inaddr);
    }
    return 1;
  }

  if (!strcasecmpend(address, ".ip6.arpa")) {
    const char *cp;
    int i;
    int n0, n1;
    struct in6_addr in6;

    if (family == AF_INET)
      return -1;

    cp = address;
    for (i = 0; i < 16; ++i) {
      n0 = hex_decode_digit(*cp++);
      if (*cp++ != '.') return -1;
      n1 = hex_decode_digit(*cp++);
      if (*cp++ != '.') return -1;
      if (n0<0 || n1 < 0)
        return -1;


      in6.s6_addr[15-i] = n0 | (n1 << 4);
    }
    if (strcasecmp(cp, "ip6.arpa"))
      return -1;

    if (result) {
      tor_addr_from_in6(result, &in6);
    }
    return 1;
  }

  if (accept_regular) {
    tor_addr_t tmp;
    int r = tor_addr_parse(&tmp, address);
    if (r < 0)
      return 0;
    if (r != family && family != AF_UNSPEC)
      return -1;

    if (result)
      memcpy(result, &tmp, sizeof(tor_addr_t));

    return 1;
  }

  return 0;
}
