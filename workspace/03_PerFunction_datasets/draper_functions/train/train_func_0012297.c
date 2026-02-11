T1Open(fn, mode)
  char *fn;
  char *mode;
{
  F_FILE *of = &TheFile;
  char c;


  Decrypt = 0;
  eexec_startOK=0;
  eexec_endOK=0;

#ifndef O_BINARY
#  define O_BINARY 0x0
#endif


  if ((of->fd=open(fn, O_RDONLY | O_BINARY)) < 0) return NULL;


  if (read( of->fd, &c, 1)!=1) {
    close( of->fd);
    return(NULL);
  }
  else
    if (c==(char)0x80){
      starthex80=1;
    }
  lseek( of->fd, 0, SEEK_SET);


  of->b_base = TheBuffer;
  of->b_size = F_BUFSIZ;
  of->b_ptr = NULL;
  of->b_cnt = 0;
  of->flags = 0;
  of->error = 0;
  haveextrach = 0;
  return &TheFile;
}
