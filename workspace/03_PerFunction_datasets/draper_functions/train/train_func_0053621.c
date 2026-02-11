gt_option_imply_either_3(GtOption *o, const GtOption *io1,
                              const GtOption *io2, const GtOption *io3)
{
  GtArray *option_array;
  gt_assert(o && io1 && io2);
  if (!o->implications)
    o->implications = gt_array_new(sizeof (GtArray*));
  option_array = gt_array_new(sizeof (GtOption*));
  gt_array_add(option_array, io1);
  gt_array_add(option_array, io2);
  gt_array_add(option_array, io3);
  gt_array_add(o->implications, option_array);
}
