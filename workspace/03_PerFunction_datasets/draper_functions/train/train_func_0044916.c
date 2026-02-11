vwarn (const char *format, __gnuc_va_list ap)
{
  int error = errno;

  flockfile (stderr);
  if (_IO_fwide (stderr, 0) > 0)
    {
#if __OPTION_POSIX_WIDE_CHAR_DEVICE_IO
      __fwprintf (stderr, L"%s: ", __progname);
      if (format)
	{
	  convert_and_print (format, ap);
	  fputws_unlocked (L": ", stderr);
	}
      __set_errno (error);
      __fwprintf (stderr, L"%m\n");
#else
      abort ();
#endif
    }
  else
    {
      fprintf (stderr, "%s: ", __progname);
      if (format)
	{
	  vfprintf (stderr, format, ap);
	  fputs_unlocked (": ", stderr);
	}
      __set_errno (error);
      fprintf (stderr, "%m\n");
    }
  funlockfile (stderr);
}
