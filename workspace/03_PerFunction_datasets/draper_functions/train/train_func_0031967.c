dispose(void)
{
  if (_dirty)
    delete[] _dirty;
  if (_bitmap)
    delete[] _bitmap;
  if (_pix_cache)
    delete[] _pix_cache;
  if (_col_cache)
    delete[] _col_cache;
}
