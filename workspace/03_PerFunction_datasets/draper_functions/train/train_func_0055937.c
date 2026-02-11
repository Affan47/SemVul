iterate_tgfsr(void)
{
  int i;
  for (i = 0; i < N - m; i++)
    x[i] = x[i + m]   ^  (x[i] >> 1)  ^  ((x[i] & 1) ? a : 0);
  for (; i < N; i++)
    x[i] = x[i + m - N] ^  (x[i] >> 1)  ^  ((x[i] & 1) ? a : 0);
}
