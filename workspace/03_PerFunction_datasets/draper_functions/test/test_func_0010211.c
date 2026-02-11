match_ip(const char *ip, struct in_addr match_addr, struct in_addr match_mask)
{
  struct in_addr addr;

  if (!looks_like_ip_addr(ip) || strchrcount(ip, '.') != 3)
	return(-1);

  if (inet_aton(ip, &addr) == 0)
	return(-1);

  if ((addr.s_addr & match_mask.s_addr) == match_addr.s_addr)
	return(1);
  return(0);
}
