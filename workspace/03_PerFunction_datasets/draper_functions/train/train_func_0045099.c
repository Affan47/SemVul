getOneChar(FILE *fp)
{
  fd_set readfds;
  struct timeval timeout;
  int fd= fileno(fp);
  int high;


  fprintf(stderr,"in getOneChar, fd=%d,fp=%p",fd,fp);
  fflush(stderr);
  if (fd == 0)
   { joe(fd);
   return -1;
   }

  while (1) {
  timeout.tv_sec = 0;
  timeout.tv_usec = 200000;
  FD_ZERO(&readfds);
  FD_SET(fd,&readfds);
  CHECK_INTERRUPT;
  high = select(fd+1,&readfds,NULL,NULL,&timeout);
  if (high > 0)
    {
      int ch ;
      fprintf(stderr,"in getOneChar, fd=%d,fp=%p",fd,fp);
      fflush(stderr);
      ch = getc(fp);
      if ( ch != EOF || feof(fp) ) {


      }
      fprintf(stderr,"in getOneChar, ch= %c,%d\n",ch,ch);
      fflush(stderr);
      CHECK_INTERRUPT;
      if (ch != EOF) return ch;
      if (feof(fp)) return EOF;
    }

  }
}
