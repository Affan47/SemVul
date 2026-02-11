iobfexpectstr(IOBFILE *iobf, char *str)
{
  char *p = str;
  int c;

  while(*p != '\0') {
    if((c = iobfgetc(iobf)) != *p++) {
      if(c != EOF)
	iobfungetc(c, iobf);
      return(p - str);
    }
  }
  return 0;
}
