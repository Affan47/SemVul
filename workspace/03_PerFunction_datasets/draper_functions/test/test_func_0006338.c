fail ( const char *format, ... )
{
    va_list arg_ptr ;

    fputs (PGMNAME ": ", stderr);
    va_start( arg_ptr, format ) ;
    vfprintf (stderr, format, arg_ptr );
    va_end(arg_ptr);
    if (*format && format[strlen(format)-1] != '\n')
      putc ('\n', stderr);
    error_count++;
}
