Zread(void *ptr, size_t size, size_t n, ZFILE *stream)
{
  long           length;

  RUNTIMECHECK;

  if (ZS->errorencountered) return 0;

  CACHEUPDATE;


  length = size * (long) n;


  if (ZS->fileposition+length > ZS->usiz)
    length = ZS->usiz - ZS->fileposition;


  if (length <= 0) return 0;


  length /= size;
  length *= size;


  if (length <= 0) return 0;


  if (BufferRead(ZS, ZS->fileposition, (unsigned char *) ptr, length))
    return 0;


  ZS->fileposition += length;


  return (size_t) (length / size);
}
