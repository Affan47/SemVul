chacha_keysetup(chacha_ctx_t *x, const unsigned char *k, unsigned kbits)
{
  const char *constants;

  x->input[4] = read32le((uint32_t *)(k + 0));
  x->input[5] = read32le((uint32_t *)(k + 4));
  x->input[6] = read32le((uint32_t *)(k + 8));
  x->input[7] = read32le((uint32_t *)(k + 12));
  if (kbits == 256) {
    k += 16;
    constants = sigma;
  } else {
    constants = tau;
  }
  x->input[8] = read32le((uint32_t *)(k + 0));
  x->input[9] = read32le((uint32_t *)(k + 4));
  x->input[10] = read32le((uint32_t *)(k + 8));
  x->input[11] = read32le((uint32_t *)(k + 12));
  x->input[0] = read32le((uint32_t *)(constants + 0));
  x->input[1] = read32le((uint32_t *)(constants + 4));
  x->input[2] = read32le((uint32_t *)(constants + 8));
  x->input[3] = read32le((uint32_t *)(constants + 12));
}
