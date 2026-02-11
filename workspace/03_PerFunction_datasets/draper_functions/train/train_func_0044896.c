swi_crc32(unsigned char *buf, int len)
{
  unsigned char *p;
  unsigned long  crc;
  if (!crc32_table[1])
    init_crc32();
  crc = 0xffffffff;
  for (p = buf; len > 0; ++p, --len)
    crc = (crc << 8) ^ crc32_table[(crc >> 24) ^ *p];
  return ~crc;
}
