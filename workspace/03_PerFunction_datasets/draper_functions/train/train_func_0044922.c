section_entry_by_name(const struct section *psection,
                                    const char *name)
{
  SECFILE_RETURN_VAL_IF_FAIL(NULL, psection, NULL != psection, NULL);

  entry_list_iterate(psection->entries, pentry) {
    if (0 == strcmp(entry_name(pentry), name)) {
      entry_use(pentry);
      return pentry;
    }
  } entry_list_iterate_end;

  return NULL;
}
