gt_spmproc_show_unit_test(GtError *err)
{
  int had_err = 0;
  GT_ENSURE_OUTPUT_DECLARE(100);

  gt_error_check(err);

  GT_ENSURE_OUTPUT(
      spmproc_show_caller(gt_spmproc_show_ascii, outfp),
      "0 + 1 + 10\n0 + 2 - 10\n2 - 0 + 10\n1 - 0 + 10\n");

  if (!had_err)
  {
    GT_ENSURE_OUTPUT(
        spmproc_a_show_caller(gt_spmproc_a_show_ascii, outfp),
        "0 + 1 + 10 11 1\n0 + 2 - 10 10 0\n"
        "2 - 0 + 10 12 2\n1 - 0 + 11 11 0\n");
  }

  return had_err;
}
