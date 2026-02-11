dnsresolve(char *name, choice level) {

#ifndef NOALARM
  extern unsigned int dnstimeout;
  extern JMP_BUF jumpbuf;
#endif
  volatile logical done = FALSE;
#ifndef MAC
  struct in6_addr addr6;
  IN_ADDR_T addr;
#ifdef VMS
  char *addrp;
#else
#ifdef AS400
  unsigned char *addrp;
#else
  const char *addrp;
#endif
#endif
  struct hostent *tempp;
#endif

  if (level < DNS_LOOKUP)
    return(FALSE);
  debug('D', "Looking up %s:", name);
#ifdef MAC
  done = IpAddr2Name(name);

#else
  addrp=NULL;
  addr = inet_addr(name);
  if (addr != INET_ADDR_ERR) {
    addrp = (char *) &addr;
  }
  else {
    if (inet_pton(AF_INET6, name, &addr6) > 0) {
      addrp = (char *) &addr6;
    }
  }
  if (addrp) {
#ifndef NOALARM
    if (SETJMP(jumpbuf))
      signal(SIGALRM, SIG_DFL);

    else {
      signal(SIGALRM, sighandler);
      alarm(dnstimeout);
#endif
      if (addr != INET_ADDR_ERR)
        tempp = gethostbyaddr(addrp, sizeof(IN_ADDR_T), AF_INET);
      else
        tempp = gethostbyaddr(addrp, sizeof(struct in6_addr), AF_INET6);
#ifndef NOALARM
      alarm(0);
      signal(SIGALRM, SIG_DFL);
#endif
      if (tempp != NULL && tempp->h_name != NULL && tempp->h_name[0] != '\0') {

	strncpy(name, tempp->h_name, BLOCKSIZE - 1);
	name[BLOCKSIZE - 1] = '\0';
	done = TRUE;
      }
#ifndef NOALARM
    }
#endif
  }
#endif
  if (done)
    debug('D', "  resolved to %s", name);
  else
    debug('D', "  can't resolve");
  return(done);
}
