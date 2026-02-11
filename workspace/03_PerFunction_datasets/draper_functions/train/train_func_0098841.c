gopengzip (char *name, char *mode)
#else
static GIO gopengzip(name, mode)
     char *name;
     char *mode;
#endif
{
  GIO gio;
  char *s;


  if( (gio = gnew()) == NULL )
    return(NULL);


  s = name;
  if( !strncasecmp(s, "gzip:", 5) ) s += 5;
  while( isspace((int)*s) ) s++;


  gio->name = xstrdup(s);
  gio->mode = xstrdup(mode);
  gio->type = GIO_GZIP;
  gio->extend = 1;


  if( !strncasecmp(name, "stdin", 5) ||
      (!strncmp(name, "-", 1) && strchr(mode, 'r')) ){
    gio->gz = (void *)gzdopen(dup(fileno(stdin)), gio->mode);
  }

  else if( !strncasecmp(name, "stdout", 6) ||
	   (!strncmp(name, "-", 1) && strchr(mode, 'w')) ){
    gio->gz = (void *)gzdopen(dup(fileno(stdout)), gio->mode);
  }

  else{
    gio->gz = (void *)gzopen(s, gio->mode);
  }
  if( gio->gz == NULL ){
    gerror(stderr, "can't open gzip'ed data file (%s)\n", s);
    goto error;
  }
  else{
    return(gio);
  }

error:
  gfree(gio);
  return(NULL);
}
