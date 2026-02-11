crc32(const Bit8u *buf, int len)
{
  const Bit8u *p;
  Bit32u crc;

  if (!crc32_table[1])
    init_crc32();

  crc = 0xffffffff;
  for (p = buf; len > 0; ++p, --len)
    crc = (crc << 8) ^ crc32_table[(crc >> 24) ^ *p];
  return ~crc;
}
