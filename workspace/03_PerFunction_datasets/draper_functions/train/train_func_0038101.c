H (uint8_t tweakey[]) {
  int i;
  uint8_t tmp[16];
  for( i = 0; i<16; i++) tmp[perm[i]] = tweakey[i];
  memcpy (tweakey, tmp, 16);

}
