__vswscanf (const wchar_t *string, const wchar_t *format, _IO_va_list args)
{
  int ret;
  _IO_strfile sf;
  struct _IO_wide_data wd;
#ifdef _IO_MTSAFE_IO
  sf._sbf._f._lock = NULL;
#endif
  _IO_no_init (&sf._sbf._f, _IO_USER_LOCK, 0, &wd, &_IO_wstr_jumps);
  _IO_fwide (&sf._sbf._f, 1);
  _IO_wstr_init_static (&sf._sbf._f, (wchar_t *)string, 0, NULL);
  ret = _IO_vfwscanf ((_IO_FILE *) &sf._sbf, format, args, NULL);
  return ret;
}
