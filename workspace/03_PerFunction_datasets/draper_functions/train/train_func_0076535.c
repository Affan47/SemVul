str_hash(const unsigned char *s, int max_len)
{
  unsigned crc;
  int i;

  if (crc_table == NULL) {
    crc_table = calloc(256, sizeof(unsigned));
    gen_crc_table();
  }
  crc = 0xFFFFFFFF;
  for (i=0; i < max_len && s[i]; i++) {
    crc = ((crc>>8) & 0x00FFFFFF) ^ crc_table[ (crc^s[i]) & 0xFF ];
  }
  return( crc^0xFFFFFFFF );
}
