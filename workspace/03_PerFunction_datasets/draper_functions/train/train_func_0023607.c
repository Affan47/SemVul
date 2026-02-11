incomplete_beta (double a, double b, double x, const char *prompt)
{
  double c;

  if (a <= 0 || b <= 0)
    {
      fprintf (stderr,
               "%s: IMPLEMENTATION ERROR! (Invalid argument in function "
               "\"incomplete_beta\")\n", prompt);
      exit (4);
    }

  if (x < 0 || x > 1)
    {
      fprintf (stderr, "%s: Value out of range (0-1)!\n", prompt);
      exit (4);
    }

  c = (DBL_IS_EQUAL(x, 0.) || DBL_IS_EQUAL(x, 1.)) ? 0 :
  exp (lngamma (a + b) - lngamma (a) - lngamma (b) + a * log (x) + b * log (1 - x));

  if (x < (a + 1) / (a + b + 2))
    return c * beta_help (a, b, x, prompt) / a;
  else
    return 1 - c * beta_help (b, a, 1 - x, prompt) / b;
}
