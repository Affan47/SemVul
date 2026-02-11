entry_str_escaped(const struct entry *pentry)
{
  SECFILE_RETURN_VAL_IF_FAIL(NULL, NULL, NULL != pentry, FALSE);
  SECFILE_RETURN_VAL_IF_FAIL(pentry->psection->secfile, pentry->psection,
                             ENTRY_STR == pentry->type, FALSE);

  return pentry->string.escaped;
}
