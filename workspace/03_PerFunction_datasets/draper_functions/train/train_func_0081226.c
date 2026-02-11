ns_mta_hexify(char *buffer, char *str, int len)
{
  char *pch = str;
  char ch;
  int i;

  for(i = 0;i < len; i ++) {
    ch = pch[i];
    buffer[2*i] = ns_mta_hextab[(ch>>4)&15];
    buffer[2*i+1] = ns_mta_hextab[ch&15];
  }

  return;
}
