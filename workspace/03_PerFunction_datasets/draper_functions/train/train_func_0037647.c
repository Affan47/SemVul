MyRand(uint32_t *seed) {
  *seed *= 16807U;
  if (*seed == 0) {
    *seed = 1;
  }
  return *seed;
}
