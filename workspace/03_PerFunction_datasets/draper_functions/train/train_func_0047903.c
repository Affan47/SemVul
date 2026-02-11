gt_safe_mult_ulong_check_func(unsigned long a, unsigned long b,
                                            const char *src_file, int src_line,
                                            GtOverflowHandlerFunc handler_func,
                                            void *data)
{
  gt_assert(sizeof (unsigned long) == 4 || sizeof (unsigned long) == 8);
  if (sizeof (unsigned long) == 4) {
    return gt_safe_mult_u32_check_func(a, b, src_file, src_line, handler_func,
                                       data);
  } else {
    return gt_safe_mult_u64_check_func(a, b, src_file, src_line, handler_func,
                                       data);
  }
}
