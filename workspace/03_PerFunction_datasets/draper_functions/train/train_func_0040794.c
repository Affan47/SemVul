NSR_TakeSourcesOnline(IPAddr *mask, IPAddr *address)
{
  int i;
  int any;

  NSR_ResolveSources();

  any = 0;
  for (i=0; i<N_RECORDS; i++) {
    if (records[i].remote_addr) {
      if (address->family == IPADDR_UNSPEC ||
          !UTI_CompareIPs(&records[i].remote_addr->ip_addr, address, mask)) {
        any = 1;
        NCR_TakeSourceOnline(records[i].data);
      }
    }
  }

  if (address->family == IPADDR_UNSPEC) {
    struct UnresolvedSource *us;

    for (us = unresolved_sources; us; us = us->next) {
      any = 1;
      us->params.online = 1;
    }
  }

  return any;
}
