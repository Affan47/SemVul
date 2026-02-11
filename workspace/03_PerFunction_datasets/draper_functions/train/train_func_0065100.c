rgba2rgba_gamma_2_2 (char *src,
                     char *dst,
                     long  samples)
{
  long n = samples;

  while (n--)
    {
      double alpha = ((double *) src)[3];
      ((double *) dst)[0] = linear_to_gamma_2_2 (((double *) src)[0]);
      ((double *) dst)[1] = linear_to_gamma_2_2 (((double *) src)[1]);
      ((double *) dst)[2] = linear_to_gamma_2_2 (((double *) src)[2]);
      ((double *) dst)[3] = alpha;
      src                += 4 * sizeof (double);
      dst                += 4 * sizeof (double);
    }
  return samples;
}
