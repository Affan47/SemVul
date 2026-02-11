cmpwrd (char *ch1, char *ch2) {

  while (*ch1==' '||*ch1=='\t') ch1++;
  while (*ch2==' '||*ch2=='\t') ch2++;

  while (*ch1 == *ch2) {
    if (*ch1==' '||*ch1=='\t'||*ch1=='\0'||*ch1=='\n'||*ch1=='\r' ) return (1);
    ch1++; ch2++;
  }

  if ( (*ch1==' '||*ch1=='\t'||*ch1=='\0'||*ch1=='\n'||*ch1=='\r') &&
       (*ch2==' '||*ch2=='\t'||*ch2=='\0'||*ch2=='\n'||*ch2=='\r') ) return (1);
  return (0);
}
