CU_get_test_pos(CU_pSuite pSuite, CU_pTest pTest)
{
  unsigned int result = 0;
  CU_ErrorCode error = CUE_SUCCESS;
  CU_pTest pCurrentTest = NULL;

  if (NULL == f_pTestRegistry) {
    error = CUE_NOREGISTRY;
  }
  else if (NULL == pSuite) {
    error = CUE_NOSUITE;
  }
  else if (NULL == pTest) {
    error = CUE_NOTEST;
  }
  else {
    pCurrentTest = pSuite->pTest;
    result = 1;
    while ((NULL != pCurrentTest) && (pCurrentTest != pTest)) {
      ++result;
      pCurrentTest = pCurrentTest->pNext;
    }
    if (pCurrentTest == NULL) {
      result = 0;
    }
  }

  CU_set_error(error);
  return result;
}
