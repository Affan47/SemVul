G (uint8_t tweakey[], uint8_t alpha) {
  int i;
  for(i=0; i<16; i++) tweakey[i] = multi (tweakey[i], alpha);
}
