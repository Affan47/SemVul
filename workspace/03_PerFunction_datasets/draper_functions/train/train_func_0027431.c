d_print_append_char (dpi, c)
     struct d_print_info *dpi;
     int c;
{
  if (dpi->buf != NULL)
    {
      if (dpi->len >= dpi->alc)
	{
	  d_print_resize (dpi, 1);
	  if (dpi->buf == NULL)
	    return;
	}

      dpi->buf[dpi->len] = c;
      ++dpi->len;
    }
}
