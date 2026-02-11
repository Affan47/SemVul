READULONG(BIO * fd,
		     unsigned long long * val) {
  signed char c;
  signed char d;
  unsigned char v[8];
  if (-1 == READALL(fd, &c, sizeof(signed char)))
    return -1;
  if ( (c > 8) || (c < 0) ) {
    fd->log(fd->context,
	    DOODLE_LOG_CRITICAL,
	    _("Assertion failed at %s:%d.\nDatabase format error!\n"),
	    __FILE__, __LINE__);
    return -1;
  }
  *val = 0;
  if (-1 == READALL(fd, &v[0], (int)c))
    return -1;
  for (d=c-1;d>=0;d--)
    (*val) += (((unsigned long long)v[(unsigned char)d]) << (8*d));
  return 0;
}
