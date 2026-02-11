VE16(uint8_t* dst) {
  int j;
  for (j = 0; j < 16; ++j) {
    memcpy(dst + j * BPS, dst - BPS, 16);
  }
}
