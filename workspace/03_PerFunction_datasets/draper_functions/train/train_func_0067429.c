isnum(genfile fd)
{
  char *errstr;

  read_line(fd,NULL);
  bhold=1;
  int tmp = strtol(linebuffer,&errstr,10);
  while (*errstr=='\n' || *errstr=='\r') errstr++;
  if (debug_da1)
    rprintf("NUMCHK: %s==>%c\n",linebuffer,*errstr);
  return (*errstr=='\0');
}
