gethostbyname2(const char *host,int AF) {
  struct hostent *hostbuf;
  struct hostent *hp;
  int res;
  int herr;

  __dns_buflen=512;
  do {
    __dns_makebuf(__dns_buflen*2); if (!__dns_buf) return 0;
    hostbuf=(struct hostent*)__dns_buf;
  } while ((res = gethostbyname2_r (host, AF, hostbuf,
				    __dns_buf+hostentsize,
				    __dns_buflen-hostentsize, &hp,
				    &herr)) == ERANGE);
  if (res) hp=0;
  return hp;
}
