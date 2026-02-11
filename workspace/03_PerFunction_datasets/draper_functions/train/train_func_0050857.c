getChar()
{
  if (!iPriv)
    return EOF;

  z_streamp z = &iPriv->iFlate;
  if (iP < (char *) z->next_out)
    return *iP++;


  if (z->avail_in == 0)
    fillBuffer();

  if (z->avail_in > 0) {

    z->next_out = (Bytef *) iOut.data();
    z->avail_out = iOut.size();
    int err = ::inflate(z, Z_NO_FLUSH);
    if (err != Z_OK && err != Z_STREAM_END) {
      ipeDebug("inflate returns error %d", err);
      ::inflateEnd(z);
      delete iPriv;
      iPriv = 0;
      return EOF;
    }
    iP = iOut.data();
    if (iP < (char *) z->next_out)
      return *iP++;

  }


  ::inflateEnd(z);
  delete iPriv;
  iPriv = 0;
  return EOF;
}
