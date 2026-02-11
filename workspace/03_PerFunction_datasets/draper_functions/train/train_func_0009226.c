beta_distr_density (double a, double b, double x, const char *prompt)
{
  if (a <= 0 || b <= 0)
    {
      fprintf (stderr,
               "%s: IMPLEMENTATION ERROR! (Invalid argument in function "
               "\"beta_distr_density\")\n", prompt);
      exit (4);
    }
  return x <= 0 ? 0 : x >= 1 ? 1 : pow (x, a - 1)
  * pow (1 - x, b - 1) / beta (a, b, prompt);
}
