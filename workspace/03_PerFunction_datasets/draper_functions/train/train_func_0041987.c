student_t_inv (double n, double p, const char *prompt)
{
  static double last_n = 1, last_p = 0.5, last_x = 0;
  double x, xx;
  static const double eps = 1e-10;

  if (n <= 0 || p <= 0 || p >= 1)
    {
      fprintf (stderr,
               "%s: IMPLEMENTATION ERROR! (Invalid argument in function "
               "\"student_t_inv\")\n", prompt);
      exit (4);
    }

  if ( DBL_IS_EQUAL(n, last_n) && DBL_IS_EQUAL(p, last_p) )
    return last_x;
  if ( DBL_IS_EQUAL(p, 0.5) )
    return 0;
  else if (p < 0.5)
    return -student_t_inv (n, 1 - p, prompt);
  else
    {
      x = 0;
      while (TRUE)
        {
          xx = x - (student_t (n, x, prompt) - p)
          / student_t_density (n, x, prompt);
          if (fabs (xx - x) < x * eps)
            break;
          x = xx;
        }
      last_n = n;
      last_p = p;
      last_x = x;
      return x;
    }
}
