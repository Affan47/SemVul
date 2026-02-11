WRITEULONG(BIO * fd,
		       unsigned long long val) {
  signed char c;
  signed char d;
  unsigned char v[8];
  unsigned long long xval;

  xval = val;
  c = 0;
  while (val > 0) {
    val = val >> 8;
    c++;
  }
  WRITEALL(fd, &c, sizeof(signed char));
  for (d=c-1;d>=0;d--)
    v[(unsigned char)d] = (unsigned char) (xval >> (8*d));
  WRITEALL(fd, &v[0], (int) c);
}
