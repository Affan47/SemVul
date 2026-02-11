FTransformWHT(const int16_t* in, int16_t* out) {

  int16_t tmp[16];
  int i;
  for (i = 0; i < 4; ++i, in += 64) {
    const int a0 = (in[0 * 16] + in[2 * 16]);
    const int a1 = (in[1 * 16] + in[3 * 16]);
    const int a2 = (in[1 * 16] - in[3 * 16]);
    const int a3 = (in[0 * 16] - in[2 * 16]);
    tmp[0 + i * 4] = a0 + a1;
    tmp[1 + i * 4] = a3 + a2;
    tmp[2 + i * 4] = a3 - a2;
    tmp[3 + i * 4] = a0 - a1;
  }
  for (i = 0; i < 4; ++i) {
    const int a0 = (tmp[0 + i] + tmp[8 + i]);
    const int a1 = (tmp[4 + i] + tmp[12+ i]);
    const int a2 = (tmp[4 + i] - tmp[12+ i]);
    const int a3 = (tmp[0 + i] - tmp[8 + i]);
    const int b0 = a0 + a1;
    const int b1 = a3 + a2;
    const int b2 = a3 - a2;
    const int b3 = a0 - a1;
    out[ 0 + i] = b0 >> 1;
    out[ 4 + i] = b1 >> 1;
    out[ 8 + i] = b2 >> 1;
    out[12 + i] = b3 >> 1;
  }
}
