Bigendian_fwrite_ints (int *array, int n, FILE *fp) {
  unsigned char buf[4];
  int value, i;

  for (i = 0; i < n; i++) {
    value = array[i];
    buf[0] = (unsigned char) (value & 0xff);
    buf[1] = (unsigned char) ((value >>= 8) & 0xff);
    buf[2] = (unsigned char) ((value >>= 8) & 0xff);
    buf[3] = (unsigned char) ((value >>= 8) & 0xff);
    if (fwrite(buf,sizeof(unsigned char),4,fp) == 0) {

      return 0;
    }
  }
  return n;
}
