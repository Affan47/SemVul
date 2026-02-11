read_number(void)
{
  char *s, *err;
  long n;

  n=1;
  do {
    if (n!=1) gen_sysmsg(218,"Please enter a *number*. ",MSG_MAIN,NULL);
    s=agt_readline(1);
    n=strtol(s,&err,10);
    if (err==s) err=NULL;
    rfree(s);
  } while (err==NULL || n<=INT_MIN || n>=INT_MAX);
  return n;
}
