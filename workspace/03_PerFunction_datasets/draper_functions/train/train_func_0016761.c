_IO_no_init (fp, flags, orientation, wd, jmp)
     _IO_FILE *fp;
     int flags;
     int orientation;
     struct _IO_wide_data *wd;
     const struct _IO_jump_t *jmp;
{
  _IO_old_init (fp, flags);
  fp->_mode = orientation;
#if defined _LIBC || defined _GLIBCPP_USE_WCHAR_T
  if (orientation >= 0)
    {
      fp->_wide_data = wd;
      fp->_wide_data->_IO_buf_base = NULL;
      fp->_wide_data->_IO_buf_end = NULL;
      fp->_wide_data->_IO_read_base = NULL;
      fp->_wide_data->_IO_read_ptr = NULL;
      fp->_wide_data->_IO_read_end = NULL;
      fp->_wide_data->_IO_write_base = NULL;
      fp->_wide_data->_IO_write_ptr = NULL;
      fp->_wide_data->_IO_write_end = NULL;
      fp->_wide_data->_IO_save_base = NULL;
      fp->_wide_data->_IO_backup_base = NULL;
      fp->_wide_data->_IO_save_end = NULL;

      fp->_wide_data->_wide_vtable = jmp;
    }
  else


    fp->_wide_data = (struct _IO_wide_data *) -1L;
#endif
  fp->_freeres_list = NULL;
}
