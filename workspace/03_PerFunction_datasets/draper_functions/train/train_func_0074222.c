set_join_field (size_t *var, size_t val)
{
  if (*var != SIZE_MAX && *var != val)
    {
      unsigned long int var1 = *var + 1;
      unsigned long int val1 = val + 1;
      error (EXIT_FAILURE, 0, _("incompatible join fields %lu, %lu"),
             var1, val1);
    }
  *var = val;
}
