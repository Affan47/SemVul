entry_int_set(struct entry *pentry, int value)
{
  SECFILE_RETURN_VAL_IF_FAIL(NULL, NULL, NULL != pentry, FALSE);
  SECFILE_RETURN_VAL_IF_FAIL(pentry->psection->secfile, pentry->psection,
                             ENTRY_INT == pentry->type, FALSE);

  pentry->integer.value = value;
  return TRUE;
}
