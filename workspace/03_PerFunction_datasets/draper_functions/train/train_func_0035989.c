crc(word_t crc_accum, word_t data)
{
  int i, j;

  if (!crc_init)
    {
      crc_gentab();
      crc_init = TRUE;
    }

  for (j=0; j < sizeof(word_t); j++)
    {
      i = ((int)(crc_accum >> 24) ^ (data >> (j*8))) & 0xff;
      crc_accum = (crc_accum << 8) ^ crc_table[i];
    }
  return crc_accum;
}
