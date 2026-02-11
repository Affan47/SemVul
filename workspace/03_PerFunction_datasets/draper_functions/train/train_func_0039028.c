string_hash(const unsigned char *str)
{
  unsigned int h = 0;
  while (*str) {
    h += *str;
    h *= 13;
    str ++;
  }
  return h % STRING_HASH_SIZE;
}
