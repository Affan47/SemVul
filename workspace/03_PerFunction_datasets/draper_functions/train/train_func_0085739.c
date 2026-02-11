garemb (char *ch) {
char *cc;
gaint cnt;
gaint qflag=0;

  cc = ch;
  cnt = 0;

  while (*ch!='\n' && *ch!='\0') {

    if (*ch == '\"' && qflag == 0) {
      qflag=1;
    } else if (*ch == '\"' && qflag == 1) {
      qflag=0;
    }

    if (((*ch!=' ') || qflag ) && (*ch!='\"')) {
      *cc = *ch;
      cc++; cnt++;
    }
    ch++;
  }
  *cc = '\0';
  return (cnt);
}
