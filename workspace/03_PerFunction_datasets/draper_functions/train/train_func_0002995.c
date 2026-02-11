set_of_1 (rtx x, const_rtx pat, void *data1)
{
  struct set_of_data *const data = (struct set_of_data *) (data1);
  if (rtx_equal_p (x, data->pat)
      || (!MEM_P (x) && reg_overlap_mentioned_p (data->pat, x)))
    data->found = pat;
}
