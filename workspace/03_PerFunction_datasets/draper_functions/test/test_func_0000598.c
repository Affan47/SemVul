console_run_all_tests(CU_pTestRegistry pRegistry)
{
  CU_pTestRegistry pOldRegistry = NULL;
  CU_ErrorCode result;

  f_pRunningSuite = NULL;

  if (NULL != pRegistry) {
    pOldRegistry = CU_set_registry(pRegistry);
  }
  result = CU_run_all_tests();
  if (NULL != pRegistry) {
    CU_set_registry(pOldRegistry);
  }
  return result;
}
