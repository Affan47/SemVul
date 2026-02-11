CU_get_suite_at_pos(unsigned int pos)
{
  CU_pSuite result = NULL;
  CU_ErrorCode error = CUE_SUCCESS;

  if (NULL == f_pTestRegistry) {
    error = CUE_NOREGISTRY;
  }
  else {
    result = CU_get_suite_by_index(pos, f_pTestRegistry);
  }

  CU_set_error(error);
  return result;
}
