hash_str(const char *src)
{
  uint32_t h = 0x2346ad27;
  const char *s = src;

  while (*s) {
    h ^= *s++ ^ (h >> 31) ^ (h >> 13) ^ (h << 4);
    h <<= 1;
  }
  return h ^ (hash_t)(s - src);
}
