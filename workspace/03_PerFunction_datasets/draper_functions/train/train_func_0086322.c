flags_set_1 (rtx x, rtx pat, void *data ATTRIBUTE_UNUSED)
{
  if (GET_CODE (pat) == SET
      && reg_overlap_mentioned_p (x, flags_set_1_rtx))
    flags_set_1_set = 1;
}
