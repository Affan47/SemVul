hostDeleteIpv4Addr (Host host)
{
  int i, j;

  if (!host->ipAddrs)
    return;
  for (i = 0, j = 0; host->ipAddrs[i]; i++) {
    if (host->ipAddrs[i]->sa_family != AF_INET)
      host->ipAddrs[j++] = host->ipAddrs[i];
  }
  host->ipAddrs[j] = 0;
  if (host->nextIpAddr >= j)
      host->nextIpAddr = 0;
}
