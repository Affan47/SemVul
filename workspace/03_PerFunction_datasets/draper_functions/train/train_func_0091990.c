_IO_wdefault_uflow (fp)
     _IO_FILE *fp;
{
  wint_t wch;
  wch = _IO_UNDERFLOW (fp);
  if (wch == WEOF)
    return WEOF;
  return *fp->_wide_data->_IO_read_ptr++;
}
