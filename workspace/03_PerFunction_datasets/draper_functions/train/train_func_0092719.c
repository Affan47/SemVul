printf_output (const char *format, ...)
#else
printf_output (format, va_alist)
     char const *format;
     va_dcl
#endif
{
  va_list args;

  VA_START (args, format);
  if (callbacks && callbacks->write_output)
    {


      const char *p = format;
      char *q;
      char *str;
      int num;
      int ch;
      char buf[100];

      while ((q = strchr (p, '%')) != NULL)
	{
	  static const char msg[] =
	    "\ninternal error: bad % in printf_output\n";
	  (*callbacks->write_output) (p, q - p);

	  switch (q[1])
	    {
	    case 's':
	      str = va_arg (args, char *);
	      (*callbacks->write_output) (str, strlen (str));
	      break;
	    case 'd':
	      num = va_arg (args, int);
	      sprintf (buf, "%d", num);
	      (*callbacks->write_output) (buf, strlen (buf));
	      break;
	    case 'c':
	      ch = va_arg (args, int);
	      buf[0] = ch;
	      (*callbacks->write_output) (buf, 1);
	      break;
	    default:
	      (*callbacks->write_output) (msg, sizeof (msg) - 1);


	      goto out;
	    }
	  p = q + 2;
	}
      (*callbacks->write_output) (p, strlen (p));
    }
  else
    vfprintf (outfile, format, args);
 out:
  va_end (args);
}
