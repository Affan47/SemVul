qsub_crc(unsigned char *Q) {
  register unsigned short crc = 0;
  register int i;

  for (i = 0; i < 10; i++)
    crc = qsub_crctab[(crc >> 8) ^ Q[i]] ^ (crc << 8);

  return (~crc)&0xFFFF;
}
