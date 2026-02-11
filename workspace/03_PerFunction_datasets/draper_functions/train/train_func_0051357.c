VE4(uint8_t* dst, const uint8_t* top) {
  const uint8_t vals[4] = {
    AVG3(top[-1], top[0], top[1]),
    AVG3(top[ 0], top[1], top[2]),
    AVG3(top[ 1], top[2], top[3]),
    AVG3(top[ 2], top[3], top[4])
  };
  int i;
  for (i = 0; i < 4; ++i) {
    memcpy(dst + i * BPS, vals, 4);
  }
}
