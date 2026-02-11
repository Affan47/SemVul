overflow (sockbuf::int_type c)


{
  if (pbase () == 0)
    return eof;

  if (c == eof)
    return sync ();

  if (pptr () == epptr ())
    sync ();
  *pptr () = (char_type)c;
  pbump (1);
  return c;
}
