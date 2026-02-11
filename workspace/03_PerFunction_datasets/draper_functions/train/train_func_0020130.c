getonebyte(void) {
  fd_set rfds;
  int res;
  char ch;
  comecho = 1;
  struct timeval timeout;
  timeout.tv_sec=0L;
  timeout.tv_usec=10000;
  FD_ZERO(&rfds);
  FD_SET(comfd, &rfds);
  res=select(comfd+1,&rfds,NULL,NULL,&timeout);
  if(res) {
    res=read(comfd,&ch,1);
    if(res==1) {
      if(comecho) {
        if(ch=='\n') lastcharnl=1;
        else {
          if(ch!='\r') lastcharnl=0;
        }

      }
      return(ch);
    }
  }
  else {
    return(-1);
  }
  return(0);
}
