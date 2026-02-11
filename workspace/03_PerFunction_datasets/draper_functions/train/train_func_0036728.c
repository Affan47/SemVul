cupsFreeOptions(
    int           num_options,
    cups_option_t *options)
{
  int	i;


  DEBUG_printf(("cupsFreeOptions(num_options=%d, options=%p)", num_options,
                options));

  if (num_options <= 0 || !options)
    return;

  for (i = 0; i < num_options; i ++)
  {
    _cupsStrFree(options[i].name);
    _cupsStrFree(options[i].value);
  }

  free(options);
}
