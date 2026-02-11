_IO_old_file_xsputn (f, data, n)
     _IO_FILE *f;
     const void *data;
     _IO_size_t n;
{
  const char *s = (char *) data;
  _IO_size_t to_do = n;
  int must_flush = 0;
  _IO_size_t count = 0;

  if (n <= 0)
    return 0;


  if ((f->_flags & _IO_LINE_BUF) && (f->_flags & _IO_CURRENTLY_PUTTING))
    {
      count = f->_IO_buf_end - f->_IO_write_ptr;
      if (count >= n)
	{
	  const char *p;
	  for (p = s + n; p > s; )
	    {
	      if (*--p == '\n')
		{
		  count = p - s + 1;
		  must_flush = 1;
		  break;
		}
	    }
	}
    }
  else if (f->_IO_write_end > f->_IO_write_ptr)
    count = f->_IO_write_end - f->_IO_write_ptr;


  if (count > 0)
    {
      if (count > to_do)
	count = to_do;
      if (count > 20)
	{
#ifdef _LIBC
	  f->_IO_write_ptr = __mempcpy (f->_IO_write_ptr, s, count);
#else
	  memcpy (f->_IO_write_ptr, s, count);
	  f->_IO_write_ptr += count;
#endif
	  s += count;
	}
      else
	{
	  char *p = f->_IO_write_ptr;
	  int i = (int) count;
	  while (--i >= 0)
	    *p++ = *s++;
	  f->_IO_write_ptr = p;
	}
      to_do -= count;
    }
  if (to_do + must_flush > 0)
    {
      _IO_size_t block_size, do_write;

      if (__overflow (f, EOF) == EOF)
	return to_do == 0 ? EOF : n - to_do;


      block_size = f->_IO_buf_end - f->_IO_buf_base;
      do_write = to_do - (block_size >= 128 ? to_do % block_size : 0);

      if (do_write)
	{
	  count = old_do_write (f, s, do_write);
	  to_do -= count;
	  if (count < do_write)
	    return n - to_do;
	}


      if (to_do)
	to_do -= _IO_default_xsputn (f, s+do_write, to_do);
    }
  return n - to_do;
}
