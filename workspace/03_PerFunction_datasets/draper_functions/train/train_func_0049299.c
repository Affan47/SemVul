plural_expression_histogram (const struct plural_distribution *self,
                             int min, int max, unsigned long j)
{
  if (min < 0)
    min = 0;


  if (max - min > 1000)
    max = min + 1000;
  if (min <= max)
    {
      const struct expression *expr = self->expr;
      unsigned long n;
      unsigned int count;


      install_sigfpe_handler ();

      count = 0;
      for (n = min; n <= max; n++)
        {
          unsigned long val = plural_eval (expr, n);

          if (val == j)
            count++;
        }


      uninstall_sigfpe_handler ();

      return count;
    }
  else
    return 0;
}
