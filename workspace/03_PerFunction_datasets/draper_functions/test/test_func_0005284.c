_IO_wdefault_finish (fp, dummy)
     _IO_FILE *fp;
     int dummy;
{
  struct _IO_marker *mark;
  if (fp->_wide_data->_IO_buf_base && !(fp->_flags2 & _IO_FLAGS2_USER_WBUF))
    {
      FREE_BUF (fp->_wide_data->_IO_buf_base,
		_IO_wblen (fp) * sizeof (wchar_t));
      fp->_wide_data->_IO_buf_base = fp->_wide_data->_IO_buf_end = NULL;
    }

  for (mark = fp->_markers; mark != NULL; mark = mark->_next)
    mark->_sbuf = NULL;

  if (fp->_IO_save_base)
    {
      free (fp->_wide_data->_IO_save_base);
      fp->_IO_save_base = NULL;
    }

#ifdef _IO_MTSAFE_IO
  if (fp->_lock != NULL)
    _IO_lock_fini (*fp->_lock);
#endif

  _IO_un_link ((struct _IO_FILE_plus *) fp);
}
