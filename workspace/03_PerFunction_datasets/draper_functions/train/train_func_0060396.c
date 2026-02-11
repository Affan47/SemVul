_djb_hash (const unsigned char *bytes, size_t len)
{
  unsigned long hash = 5381;
  while (len--) {
    unsigned char c = *bytes++;
    hash *= 33;
    hash ^= c;
  }
  return hash;
}
