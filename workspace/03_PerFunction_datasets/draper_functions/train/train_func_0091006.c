parse_netmask(const char *text, struct irc_ssaddr *addr, int *b)
{
#ifdef IPV6
    if (strchr(text, ':'))
    return try_parse_v6_netmask(text, addr, b);
#endif
  if (strchr(text, '.'))
    return try_parse_v4_netmask(text, addr, b);
  return HM_HOST;
}
