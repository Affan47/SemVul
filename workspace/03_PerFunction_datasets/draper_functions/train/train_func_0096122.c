_IO_old_do_write (fp, data, to_do)
     _IO_FILE *fp;
     const char *data;
     _IO_size_t to_do;
{
  return (to_do == 0 || (_IO_size_t) old_do_write (fp, data, to_do) == to_do)
	 ? 0 : EOF;
}
