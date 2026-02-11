colSetName(VimosColumn *column, const char *name)
{

  size_t sz;

  if (!column)
    return EXIT_FAILURE;

  if ((sz = strlen(name)) > VM_DESC_LENGTH - 1)
    return EXIT_FAILURE;

  memcpy(column->colName, name, sz);
  *(column->colName + sz) = '\0';

  return EXIT_SUCCESS;

}
