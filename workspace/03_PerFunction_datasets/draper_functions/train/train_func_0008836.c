set_stream(GP<ByteStream> xibs)
{
  GUTF8String name;
  static unsigned long serial=0;
  pool=DataPool::create(xibs);
  name.format("data://%08lx/%08lx.djvu",
    ++serial,(unsigned long)(size_t)((const ByteStream *)xibs));
  pool_url=GURL::UTF8(name);
  return pool_url;
}
