poly_extrap (gsl_matrix * d,
             const double x[],
             const unsigned int i_step,
             const double x_i,
             const double y_i[],
             double y_0[], double y_0_err[], double work[], const size_t dim)
{
  size_t j, k;

  DBL_MEMCPY (y_0_err, y_i, dim);
  DBL_MEMCPY (y_0, y_i, dim);

  if (i_step == 0)
    {
      for (j = 0; j < dim; j++)
        {
          gsl_matrix_set (d, 0, j, y_i[j]);
        }
    }
  else
    {
      DBL_MEMCPY (work, y_i, dim);

      for (k = 0; k < i_step; k++)
        {
          double delta = 1.0 / (x[i_step - k - 1] - x_i);
          const double f1 = delta * x_i;
          const double f2 = delta * x[i_step - k - 1];

          for (j = 0; j < dim; j++)
            {
              const double q_kj = gsl_matrix_get (d, k, j);
              gsl_matrix_set (d, k, j, y_0_err[j]);
              delta = work[j] - q_kj;
              y_0_err[j] = f1 * delta;
              work[j] = f2 * delta;
              y_0[j] += y_0_err[j];
            }
        }

      for (j = 0; j < dim; j++)
        {
          gsl_matrix_set (d, i_step, j, y_0_err[j]);
        }
    }
}
