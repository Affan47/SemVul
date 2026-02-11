prhex(unsigned char *p, int leng) {

  int n;
  int pos = 25;

  for(n = 0; n < leng; n++, p++) {
    if (fold && pos >= fold) {
      printf ("\\\n\t%02x", *p);
      pos = 14;
    } else {
      printf(" %02x", *p);
      pos += 3;
    }
  }
  printf("\n");
}
