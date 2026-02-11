gt_divergence(double E,
                   double T,
                   double M,
                   double threshold,
                   double shulen,
                   unsigned long subjectLength,
                   double gc,
                   double *ln_n_fac,
                   unsigned long n_s)
{
  double p, q,
         du, dl, dm, d, exp_shulen;
  double *s1;
  s1 = gt_calloc((size_t) n_s + 1, sizeof (double));

  p = gc / 2;
  q = (1.0 - gc) / 2.0;
  du = 0.0;
  dl = 1.0 - (2 * p * p + 2 * q * q);

  while (gt_double_smaller_double(threshold, (dl - du) / 2.0)) {
    dm = (du + dl) / 2.0;
    exp_shulen = expShulen(T, M, dm, p, subjectLength, ln_n_fac, s1, n_s);
    if (gt_double_smaller_double(shulen, exp_shulen))
      du = dm;
    else
      dl = dm;


    if (fabs (dl - du) / dl <= E)
      break;
  }
  d = (du + dl) / 2.0;
  gt_free(s1);
  return d;
}
