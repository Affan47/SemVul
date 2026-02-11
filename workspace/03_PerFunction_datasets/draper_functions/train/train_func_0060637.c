bit(char b) {
  static int nbit = 0;
  printf("%d", b);
  if (nbit % OBUFLEN == 0)
    fflush(0);
  nbit++;
}
