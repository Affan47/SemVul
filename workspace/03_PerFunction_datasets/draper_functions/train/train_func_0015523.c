loader_BASICODE_load(const char *filename,
		     unsigned char *data,
		     long size,
		     fileio_prop_t **prop)
{
  int newline;
  long a, xsize;
  unsigned char c, *sptr, *dptr;

  *prop = (fileio_prop_t *)malloc(sizeof(fileio_prop_t));
  if (*prop == NULL)
    return -1;
  memset(*prop, 0, sizeof(fileio_prop_t));

  (*prop)->type = FILEIO_TYPE_BASICODE;
  (*prop)->valid = FILEIO_V_NONE;
  (*prop)->load_addr = 0;
  (*prop)->start_addr = 0;
  (*prop)->autostart  = 0;
  loader_BASICODE_set_filename((*prop)->name, filename);

  (*prop)->data = (unsigned char *)malloc(size);
  if ((*prop)->data == 0)
    return -1;

  sptr = data;
  dptr = (*prop)->data;
  newline = xsize = 0;
  for (a = 0;a < size;a++)
    {
      c = *sptr++;


      if (c == 0x0a)
	c = 0x0d;


      if (c == 0x0d)
	{
	  if (newline)
	    continue;
	  else
	    newline = 1;
	}
      else
	{
	  newline = 0;
	}

      *dptr = c;
      dptr++;
      xsize++;
    }

  (*prop)->size = xsize;
  return 0;
}
