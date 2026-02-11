seek(long offset, int whence, bool nothrow)
{
  if (whence==SEEK_SET && offset>=0 && offset==ftell(fp))
    return 0;
  clearerr(fp);
  if (fseek(fp, offset, whence))
    {
      if (nothrow)
        return -1;
      G_THROW(strerror(errno));
    }
  return tell();
}
