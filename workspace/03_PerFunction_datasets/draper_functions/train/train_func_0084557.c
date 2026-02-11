mb_fragment_len(const char *str)
{
  unsigned char c = *((const unsigned char *)str);
  if (c < 0x80) {
    return 1;
  }
  if (c < 0xe0) {
    return 2;
  }
  if (c < 0xf0) {
    return 3;
  }
  if (c < 0xf8) {
    return 4;
  }
  if (c < 0xfc) {
    return 5;
  }
  return 6;
}
