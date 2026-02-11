resolve_hostname(struct in_addr ip)
{
  struct hostent *reverse, *forward;
  struct dns_cache *dns;
  char *pnt, fqdn[HOSTLEN];

  dns = dns_first;
  while (dns != NULL) {
    if (ip.s_addr == dns->ip.s_addr) {
      if (opt.verbose) {
	fprintf(stderr, _("Resolving %s from cache\n"), inet_ntoa(ip));
      }
      return (dns->fqdn);
    }
    dns = dns->next;
  }

  if (opt.verbose)
    fprintf(stderr, _("Resolving %s\n"), inet_ntoa(ip));

  reverse = gethostbyaddr((void *) &ip.s_addr, sizeof(struct in_addr), AF_INET);

  if ((reverse != NULL) && (reverse->h_name != NULL)) {
    if ((unsigned int) reverse->h_length > sizeof(struct in_addr)) {
      fprintf(stderr, _("Wrong host name size\n"));
      reverse->h_length = sizeof(struct in_addr);
      reverse->h_name[reverse->h_length] = '\0';
    }

    pnt = reverse->h_name;
    while (*pnt != '\0') {
      if (isalnum((int) *pnt) || *pnt == '.' || *pnt == '-') {
	pnt++;
	continue;
      } else {
	*pnt = '_';
	pnt++;
      }
    }

    if (opt.verbose)
      fprintf(stderr, _("Resolving %s\n"), reverse->h_name);

    forward = gethostbyname(reverse->h_name);
    if ((forward != NULL) && (forward->h_addr_list[0]) != NULL) {
      if (strncmp(inet_ntoa(ip), inet_ntoa(*(struct in_addr *) forward->h_addr_list[0]), IPLEN) == 0) {
	xstrncpy(fqdn, reverse->h_name, HOSTLEN);
      } else {
	snprintf(fqdn, HOSTLEN, _("%s [forward lookup: %s]"), reverse->h_name, inet_ntoa(*(struct in_addr *) forward->h_addr_list[0]));
      }
    } else {
      snprintf(fqdn, HOSTLEN, _("%s [forward lookup failed]"), reverse->h_name);
    }
  } else {
    xstrncpy(fqdn, "-", HOSTLEN);
  }

  dns = xmalloc(sizeof(struct dns_cache));
  dns->ip.s_addr = ip.s_addr;
  dns->fqdn = xmalloc(strlen(fqdn) + 1);
  xstrncpy(dns->fqdn, fqdn, strlen(fqdn) + 1);
  dns->next = dns_first;
  dns_first = dns;

  return (dns->fqdn);
}
