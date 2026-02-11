store_type(void *elem, void *data,
                                   GT_UNUSED GtError *err)
{
  GtStrArray *types = data;
  gt_error_check(err);
  gt_assert(elem && types);
  gt_str_array_add_cstr(types, *(char**) elem);
  return CONTINUE_ITERATION;
}
