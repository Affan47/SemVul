gsl_histogram2d_cov (const gsl_histogram2d * h)
{
  const double xmean = gsl_histogram2d_xmean (h);
  const double ymean = gsl_histogram2d_ymean (h);
  const size_t nx = h->nx;
  const size_t ny = h->ny;
  size_t i;
  size_t j;


  long double wcovariance = 0;
  long double W = 0;

  for (j = 0; j < ny; j++)
    {
      for (i = 0; i < nx; i++)
        {
          double xi = (h->xrange[i + 1] + h->xrange[i]) / 2.0 - xmean;
          double yj = (h->yrange[j + 1] + h->yrange[j]) / 2.0 - ymean;
          double wij = h->bin[i * ny + j];

          if (wij > 0)
            {
              W += wij;
              wcovariance += ((xi * yj) - wcovariance) * (wij / W);
            }
        }
    }

  return wcovariance;

}
