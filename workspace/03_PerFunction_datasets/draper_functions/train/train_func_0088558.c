READULONGPAIR(BIO * fd,
			 unsigned long long * val1,
			 unsigned long long * val2) {
  unsigned char c;
  signed char d;
  unsigned char v[8];

  if (-1 == READALL(fd, &c, sizeof(unsigned char)))
    return -1;
  if ( ((c & 15) > 8) || ( (c>>4) > 8) ) {
    fd->log(fd->context,
	    DOODLE_LOG_CRITICAL,
	    _("Assertion failed at %s:%d.\nDatabase format error!\n"),
	    __FILE__, __LINE__);
    return -1;
  }
  *val1 = 0;
  *val2 = 0;
  if (-1 == READALL(fd, &v[0], (unsigned char) c & 15))
    return -1;
  for (d=(c&15)-1;d>=0;d--)
    (*val2) += (((unsigned long long)v[(unsigned char)d]) << (8*d));
  if (-1 == READALL(fd, &v[0], (unsigned char) c >> 4))
    return -1;
  for (d=(c>>4)-1;d>=0;d--)
    (*val1) += (((unsigned long long)v[(unsigned char)d]) << (8*d));
  return 0;
}
