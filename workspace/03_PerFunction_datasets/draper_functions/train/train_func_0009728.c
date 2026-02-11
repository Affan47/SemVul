poserror(pos_type *pos, char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  fprintf(stderr, "%s:%u: error: ",
	  pos->srcpath == NULL ? "stdin" : pos->srcpath,
	  pos->linenum);
  vfprintf(stderr, fmt, ap);
  fprintf(stderr, "\n");
  errorcount++;
  va_end(ap);
}
