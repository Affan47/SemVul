tty_fprintf (FILE *fp, const char *fmt, ... )
{
  va_list arg_ptr;

  if (fp)
    {
      va_start (arg_ptr, fmt) ;
      vfprintf (fp, fmt, arg_ptr );
      va_end (arg_ptr);
      return;
    }

  if (no_terminal)
    return;

  if( !initialized )
    init_ttyfp();

    va_start( arg_ptr, fmt ) ;
#ifdef _WIN32
    {
        char *buf = NULL;
        int n;
	DWORD nwritten;

	n = vasprintf(&buf, fmt, arg_ptr);
	if( !buf )
	    log_bug("vasprintf() failed\n");

	if( !WriteConsoleA( con.out, buf, n, &nwritten, NULL ) )
	    log_fatal("WriteConsole failed: rc=%d", (int)GetLastError() );
	if( n != nwritten )
	    log_fatal("WriteConsole failed: %d != %d\n", n, (int)nwritten );
	last_prompt_len += n;
        xfree (buf);
    }
#else
    last_prompt_len += vfprintf(ttyfp,fmt,arg_ptr) ;
    fflush(ttyfp);
#endif
    va_end(arg_ptr);
}
