ascii_fields(char **fp,int maxfp,char *inbuf,const char *delim)
{
  int n=0;
  while((*fp = strsep(&inbuf,delim)) != NULL && n < maxfp) {
    n++;
    fp++;
  }
  return ( n < maxfp ? n : 0 );
}
