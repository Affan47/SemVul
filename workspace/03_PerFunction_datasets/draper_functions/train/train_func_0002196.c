gioparseipport (char *host, unsigned int *ip, unsigned short *port)
#else
static int gioparseipport(host, ip, port)
     char *host;
     unsigned int *ip;
     unsigned short *port;
#endif
{
  char *s1, *p1, *p2;
  int got;


  *ip = 0;
  *port = 0;


  if( !host || !*host )
    return(0);


  s1 = xstrdup(host);
  if( !(p1 = (char *)strchr(s1, ':')) ){
    got = 0;
    goto done;
  }
  *p1 = '\0';
  p1++;


  p2 = NULL;
  *port = (unsigned short)strtol(p1, &p2, 0);

  if( *port <=0 || (p1 == p2) ){
    *port = 0;
    got = 0;
    goto done;
  }


  if( (*ip = giohostip(s1)) == 0 ){
    *port = 0;
    got = 0;
  }
  else{
    got = 1;
  }

done:
  xfree(s1);
  return(got);
}
