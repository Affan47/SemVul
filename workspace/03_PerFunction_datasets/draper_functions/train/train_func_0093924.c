crc32(const void *buf, unsigned int size) {
  const unsigned char *p;
  unsigned int crc;

  p = buf;
  crc = ~0U;

  while (size--)
    crc = crc32_tab[(crc ^ *p++) & 0xFF] ^ (crc >> 8);

  return crc ^ ~0U;
}
