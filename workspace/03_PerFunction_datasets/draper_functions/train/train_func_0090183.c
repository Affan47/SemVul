close(void)
{
  if (_context != NULL)
    {
      th_encode_free(_context);
      _context = NULL;
    }

  if (_f != NULL)
    {
      fclose(_f);
      _f = NULL;
    }

  if (_buf_y != NULL)
    {
      delete[] _buf_y;
      delete[] _buf_u;
      delete[] _buf_v;
      _buf_y = _buf_u = _buf_v = NULL;
    }
}
