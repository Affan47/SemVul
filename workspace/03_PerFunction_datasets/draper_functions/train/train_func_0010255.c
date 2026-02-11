gt_str_array_delete(GtStrArray *sa)
{
  unsigned long i;
  if (!sa) return;
  if (sa->reference_count) {
    sa->reference_count--;
    return;
  }
  for (i = 0; i < gt_array_size(sa->strings); i++)
    gt_str_delete(*(GtStr**) gt_array_get(sa->strings, i));
  gt_array_delete(sa->strings);
  gt_free(sa);
}
