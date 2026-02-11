gt_str_array_add_cstr(GtStrArray *sa, const char *cstr)
{
  GtStr *str;
  gt_assert(sa && cstr);
  str = gt_str_new_cstr(cstr);
  gt_array_add(sa->strings, str);
}
