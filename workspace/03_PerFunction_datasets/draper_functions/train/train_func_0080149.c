ipv4_integer2bin(unsigned long ip_int, char* ip_bin)
{
  int i = 31;
  for (; i >= 0; i--) {
    if (i == 23 || i == 15 || i == 7)
      *ip_bin++ = '.';
    unsigned long bit = (ip_int & (1 << i));
    *ip_bin = bit ? '1' : '0';
    ip_bin++;
  }
  *ip_bin = 0;
  return 0;
}
