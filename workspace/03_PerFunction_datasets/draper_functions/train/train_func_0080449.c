__woverflow (f, wch)
     _IO_FILE *f;
     wint_t wch;
{
  if (f->_mode == 0)
    _IO_fwide (f, 1);
  return _IO_OVERFLOW (f, wch);
}
