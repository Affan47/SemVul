LAME_getnext(struct LAME *l) {
  double x;
  uint8_t ret;

  LAME_fpusht(l);
  x = LAME_fpusht(l) * 256.0;
  if ((int32_t)x < 256) ret = (uint8_t)x;
  else ret=0xff;
  return ret;
}
