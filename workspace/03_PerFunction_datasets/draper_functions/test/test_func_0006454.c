has_extended_option(GtArray *options)
{
  unsigned long i;
  GtOption *option;
  gt_assert(options);
  for (i = 0; i < gt_array_size(options); i++) {
    option = *(GtOption**) gt_array_get(options, i);
    if (option->is_extended_option)
      return true;
  }
  return false;
}
