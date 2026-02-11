bin1 (gfloat * x, gint n, gfloat * ab, gint nbin, gint * nc)
{


  gint i, k, nskip;
  gfloat a, b, d;

  nskip = 0;
  a = ab[0];
  b = ab[1];

  for (i = 0; i < nbin; i++)
    nc[i] = 0;

  d = (b - a) / (gfloat) nbin;

  for (i = 0; i < n; i++) {
    k = (gint) ((x[i] - a) / d) + 1;
    if (k >= 1 && k <= nbin)
      nc[k] += 1;
    else
      nskip += 1;
  }

  return nskip;
}
