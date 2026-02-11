_glh_load_history(GlHistory *glh, const char *filename, const char *comment,
		      char *line, size_t dim)
{
#ifdef WITHOUT_FILE_SYSTEM
  _err_record_msg(glh->err, "Can't load history without filesystem access",
		  END_ERR_MSG);
  errno = EINVAL;
  return 1;
#else
  FILE *fp;
  size_t comment_len;
  time_t timestamp;
  unsigned group;

  int lineno;


  if(!glh || !filename || !comment || !line) {
    if(glh)
      _err_record_msg(glh->err, "NULL argument(s)", END_ERR_MSG);
    errno = EINVAL;
    return 1;
  };


  comment_len = strlen(comment);


  _glh_clear_history(glh, 1);


  fp = fopen(filename, "r");
  if(!fp)
    return 0;


  for(lineno=1; fgets(line, dim, fp) != NULL; lineno++) {
    char *lptr;


    if(strncmp(line, comment, comment_len) != 0) {
      return _glh_cant_load_history(glh, filename, lineno,
				    "Corrupt history parameter line", fp);
    };


    for(lptr=line+comment_len; *lptr && (*lptr==' ' || *lptr=='\t'); lptr++)
      ;


    if(_glh_decode_timestamp(lptr, &lptr, &timestamp)) {
      return _glh_cant_load_history(glh, filename, lineno,
				    "Corrupt timestamp", fp);
    };


    while(*lptr==' ' || *lptr=='\t')
      lptr++;


    group = (int) strtoul(lptr, &lptr, 10);
    if(*lptr != ' ' && *lptr != '\n') {
      return _glh_cant_load_history(glh, filename, lineno,
				    "Corrupt group id", fp);
    };


    while(*lptr==' ' || *lptr=='\t')
      lptr++;


    if(*lptr != '\n') {
      return _glh_cant_load_history(glh, filename, lineno,
				    "Corrupt parameter line", fp);
    };


    lineno++;
    if(fgets(line, dim, fp) == NULL)
      return _glh_cant_load_history(glh, filename, lineno, "Read error", fp);


    if(_glh_add_history(glh, line, 1)) {
      return _glh_cant_load_history(glh, filename, lineno,
				    "Insufficient memory to record line", fp);
    };


    if(glh->list.tail) {
      glh->list.tail->timestamp = timestamp;
      glh->list.tail->group = group;
    };
  };


  (void) fclose(fp);
  return 0;
#endif
}
