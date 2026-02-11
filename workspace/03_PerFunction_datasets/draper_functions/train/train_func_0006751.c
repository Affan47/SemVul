print_quoted (FILE *fp,
	      const struct quoting_options *qopts,
	      bool dest_is_tty,
	      const char *format,
	      const char *s)
{
  int rv;

  if (dest_is_tty)
    {
      char smallbuf[BUFSIZ];
      size_t len = quotearg_buffer (smallbuf, sizeof smallbuf, s, -1, qopts);
      char *buf;
      if (len < sizeof smallbuf)
	buf = smallbuf;
      else
	{


	  buf = xmalloc (len + 1);
	  quotearg_buffer (buf, len + 1, s, -1, qopts);
	}


      len = qmark_chars(buf, len);

      rv = fprintf(fp, format, buf);
      if (buf != smallbuf)
	{
	  free(buf);
	  buf = NULL;
	}
    }
  else
    {

      rv = fprintf(fp, format, s);
    }
  return rv;
}
