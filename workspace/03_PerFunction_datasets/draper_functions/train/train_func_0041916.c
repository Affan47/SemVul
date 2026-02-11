hc128_init(hc128_state *state, const uint8_t *key, const uint8_t *iv)
{
  unsigned int i;
  uint32_t w[1280];

  for(i = 0; i < 4; ++i) {
    w[i] = w[i+4] = pack_littleendian(key + 4 * i);
    w[i+8] = w[i+12] = pack_littleendian(iv + 4 * i);
  }

  for(i = 16; i < 1280; ++i) {
    w[i] = f2(w[i-2]) + w[i-7] + f1(w[i-15]) + w[i-16] + i;
  }

  uint32_t *p = state->p;
  uint32_t *q = state->q;

  for(i = 0; i < 512; ++i)
    {
      p[i] = w[i+256];
      q[i] = w[i+768];
    }

  for(i = 0; i < 512; ++i)
    p[i] = round_expression(p, q, g1, i);

  for(i = 0; i < 512; ++i)
    q[i] = round_expression(q, p, g2, i);

  state->i = 0;
}
