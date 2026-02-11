gopenfile (char *name, char *mode)
#else
static GIO gopenfile(name, mode)
     char *name;
     char *mode;
#endif
{
  char *s;
  GIO gio;


  if( (gio = gnew()) == NULL )
    return(NULL);


  s = name;
  if( !strncasecmp(s, "file:", 5) ) s += 5;
  if( !strncasecmp(s, "unfile:", 7) ){
    gio->unbuffered = 1;
    s += 7;
  }
  while( isspace((int)*s) ) s++;


  gio->name = xstrdup(s);
  gio->type = GIO_DISK;
  gio->extend = 1;
  gio->mode = xstrdup(mode);


  gio->fp = fopen(s, gio->mode);
  if( gio->fp == NULL ){
    gerror(stderr, "can't open data file (%s)\n", s);
    goto error;
  }
  else{
    return(gio);
  }

error:
  gfree(gio);
  return(NULL);
}
