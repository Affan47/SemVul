logOrPrint (int level, FILE *fp, const char *fmt, ...)
{
  va_list ap ;

  va_start (ap,fmt) ;
  if (fp != NULL)
    {
      vfprintf (fp,fmt,ap) ;
      fputc ('\n',fp) ;
    }
  else
    {
      char buffer [512] ;

      vsnprintf (buffer,sizeof buffer,fmt,ap) ;
      syslog (level,buffer) ;
    }
  va_end (ap) ;
}
