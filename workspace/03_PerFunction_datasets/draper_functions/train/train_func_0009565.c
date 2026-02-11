gt_trans_table_get_scheme_descriptions()
{
  unsigned long i;
  GtTranslationScheme *scheme;
  GtStr *str;
  GtStrArray *sa = gt_str_array_new();
  str = gt_str_new();
  for (i = 1UL; i < (unsigned long) GT_SIZEOFTRANSRANGE; i++) {
    if (transnum2index[i] == GT_UNDEFTRANSNUM)
      continue;
    scheme = schemetable + transnum2index[i];
    gt_str_reset(str);
    gt_str_append_uint(str, scheme->identity);
    gt_str_append_cstr(str, ": ");
    gt_str_append_cstr(str, scheme->name);
    gt_str_array_add_cstr(sa, gt_str_get(str));
  }
  gt_str_delete(str);
  return sa;
}
