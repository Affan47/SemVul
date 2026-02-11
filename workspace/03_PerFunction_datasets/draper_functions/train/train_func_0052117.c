tag_line(GtIO *obo_file, GtStr *tag, GtStr *value, GtError *err)
{
  int had_err;
  gt_error_check(err);
  gt_assert(obo_file && tag && value);
  do {
    had_err = proc_any_char(obo_file, tag, false, err);
  } while (!had_err && any_char(obo_file, false));
  if (!had_err)
    had_err = gt_io_expect(obo_file, OBO_SEPARATOR_CHAR, err);
  while (!had_err && gt_io_peek(obo_file) == OBO_BLANK_CHAR)
    gt_io_next(obo_file);
  if (!had_err) {
    do {
      had_err = proc_any_char(obo_file, value, true, err);
    } while (!had_err && any_char(obo_file, true));
  }
  if (!had_err) {
    if (gt_io_peek(obo_file) == OBO_COMMENT_CHAR)
      had_err = comment_line(obo_file, err);
    else
      had_err = gt_io_expect(obo_file, GT_END_OF_LINE, err);
  }
  return had_err;
}
