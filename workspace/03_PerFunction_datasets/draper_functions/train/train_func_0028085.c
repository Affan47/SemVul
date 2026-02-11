srunner_add_failure (SRunner *sr, TestResult *tr)
{
  check_list_add_end (sr->resultlst, tr);
  sr->stats->n_checked++;
  if (tr->rtype == CK_FAILURE)
    sr->stats->n_failed++;
  else if (tr->rtype == CK_ERROR)
    sr->stats->n_errors++;

}
