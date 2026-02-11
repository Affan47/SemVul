read_integer(char &c, ByteStream &bs)
{
  unsigned int x = 0;

  while (c==' ' || c=='\t' || c=='\r' || c=='\n' || c=='#')
    {
      if (c=='#')
        do { } while (bs.read(&c,1) && c!='\n' && c!='\r');
      c = 0;
      bs.read(&c, 1);
    }

  if (c<'0' || c>'9')
    G_THROW( ERR_MSG("GBitmap.not_int") );

  while (c>='0' && c<='9')
    {
      x = x*10 + c - '0';
      c = 0;
      bs.read(&c, 1);
    }
  return x;
}
