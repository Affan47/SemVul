_IO_wstr_count (fp)
     _IO_FILE *fp;
{
  struct _IO_wide_data *wd = fp->_wide_data;

  return ((wd->_IO_write_ptr > wd->_IO_read_end
	   ? wd->_IO_write_ptr : wd->_IO_read_end)
	  - wd->_IO_read_base);
}
