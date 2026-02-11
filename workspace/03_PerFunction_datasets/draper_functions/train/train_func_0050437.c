gethostbyname (const char *host) {
  struct hostent *hostbuf;
  struct hostent *hp;
  int res;

  __dns_buflen=512;
  do {
    __dns_makebuf(__dns_buflen*2); if (!__dns_buf) return 0;
    hostbuf=(struct hostent*)__dns_buf;
  } while ((res = gethostbyname_r (host, hostbuf, __dns_buf+hostentsize,
				   __dns_buflen-hostentsize, &hp,
				   &h_errno)) == ERANGE);
  if (res) hp=0;
  return hp;
}
