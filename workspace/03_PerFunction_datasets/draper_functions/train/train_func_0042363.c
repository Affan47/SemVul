error (const char *fmt, ...) {
     va_list args;

     if (mount_quiet)
	  return;
     va_start (args, fmt);
     vfprintf (stderr, fmt, args);
     va_end (args);
     fputc('\n', stderr);
}
