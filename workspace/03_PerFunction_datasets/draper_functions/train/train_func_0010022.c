cdb_hash(const void *buf, unsigned len)
{
  register const unsigned char *p = (const unsigned char *)buf;
  register const unsigned char *end = p + len;
  register unsigned hash = 5381;
  while (p < end)
    hash = (hash + (hash << 5)) ^ *p++;
  return hash;
}
