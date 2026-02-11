main(int i, char const * argv[])
{
  real rate           = atof(argv[1]),
       lead_in_len    = atof(argv[2]),
       len            = atof(argv[3]),
       sweep_to_freq  = atof(argv[4]),
       multiplier     = atof(argv[5]),
       f1 = -sweep_to_freq / len * lead_in_len, f2 = sweep_to_freq,
       n1 = rate * -lead_in_len, n2 = rate * len,
       m = (f2 - f1) / (n2 - n1) / 2, dummy;
  FILE * file = fopen(argv[6], "wb");
  i = (int)n1;
  if (!file || i != n1)
    exit(1);
  for (; i < (int)(n2 + .5); ++i) {
    double d1 = multiplier * sin(2 * M_PI * modf(i * m * i / rate, &dummy));
    double d = i < 0? d1 * (1 - cos(M_PI * (i + n1) / n1)) * .5 : d1;
#if QUAD
    size_t actual = fwrite(&d, sizeof(d), 1, file);
#else
    int32_t out = rint32(d * (32768. * 65536 - 1));
    size_t actual = fwrite(&out, sizeof(out), 1, file);
#endif
    if (actual != 1)
      return 1;
  }
  return 0;
}
