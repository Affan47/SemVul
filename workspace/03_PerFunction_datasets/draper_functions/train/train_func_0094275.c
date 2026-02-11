gt_option_imply(GtOption *o, const GtOption *implied_option)
{
  GtArray *option_array;
  gt_assert(o && implied_option);
  if (!o->implications)
    o->implications = gt_array_new(sizeof (GtArray*));
  option_array = gt_array_new(sizeof (GtOption*));
  gt_array_add(option_array, implied_option);
  gt_array_add(o->implications, option_array);
}
