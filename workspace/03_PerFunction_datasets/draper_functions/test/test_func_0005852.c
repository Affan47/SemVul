case_values_threshold (void)
{
  unsigned int threshold = PARAM_VALUE (PARAM_CASE_VALUES_THRESHOLD);

  if (threshold == 0)
    threshold = targetm.case_values_threshold ();

  return threshold;
}
