conversion_error_other (int errnum, const char* infilename)
{
  fflush(stdout);
  if (column > 0)
    putc('\n',stderr);
  error(0,errnum,


        _("%s:%u:%u"),
        infilename,line,column);
}
