__wunderflow (fp)
     _IO_FILE *fp;
{
  if (fp->_mode < 0 || (fp->_mode == 0 && _IO_fwide (fp, 1) != 1))
    return WEOF;

  if (fp->_mode == 0)
    _IO_fwide (fp, 1);
  if (_IO_in_put_mode (fp))
    if (_IO_switch_to_wget_mode (fp) == EOF)
      return WEOF;
  if (fp->_wide_data->_IO_read_ptr < fp->_wide_data->_IO_read_end)
    return *fp->_wide_data->_IO_read_ptr;
  if (_IO_in_backup (fp))
    {
      _IO_switch_to_main_wget_area (fp);
      if (fp->_wide_data->_IO_read_ptr < fp->_wide_data->_IO_read_end)
	return *fp->_wide_data->_IO_read_ptr;
    }
  if (_IO_have_markers (fp))
    {
      if (save_for_wbackup (fp, fp->_wide_data->_IO_read_end))
	return WEOF;
    }
  else if (_IO_have_backup (fp))
    _IO_free_wbackup_area (fp);
  return _IO_UNDERFLOW (fp);
}
