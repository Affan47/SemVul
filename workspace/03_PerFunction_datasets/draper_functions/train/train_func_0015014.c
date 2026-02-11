secfile_insert_bitwise_enum_full(struct section_file *secfile,
                                               int bitwise_val,
                                               secfile_enum_name_fn_t
                                               name_fn,
                                               secfile_enum_iter_fn_t
                                               begin_fn,
                                               secfile_enum_iter_fn_t
                                               end_fn,
                                               secfile_enum_next_fn_t
                                               next_fn,
                                               const char *comment,
                                               bool allow_replace,
                                               const char *path, ...)
{
  char fullpath[MAX_LEN_SECPATH], string[MAX_LEN_SECPATH];
  const char *ent_name;
  struct section *psection;
  struct entry *pentry = NULL;
  va_list args;
  int i;

  SECFILE_RETURN_VAL_IF_FAIL(secfile, NULL, NULL != secfile, NULL);
  SECFILE_RETURN_VAL_IF_FAIL(secfile, NULL, NULL != name_fn, NULL);
  SECFILE_RETURN_VAL_IF_FAIL(secfile, NULL, NULL != begin_fn, NULL);
  SECFILE_RETURN_VAL_IF_FAIL(secfile, NULL, NULL != end_fn, NULL);
  SECFILE_RETURN_VAL_IF_FAIL(secfile, NULL, NULL != next_fn, NULL);


  string[0] = '\0';
  if (0 != bitwise_val) {
    for (i = begin_fn(); i != end_fn(); i = next_fn(i)) {
      if (i & bitwise_val) {
        if ('\0' == string[0]) {
          sz_strlcpy(string, name_fn(i));
        } else {
          cat_snprintf(string, sizeof(string), "|%s", name_fn(i));
        }
      }
    }
  }

  va_start(args, path);
  fc_vsnprintf(fullpath, sizeof(fullpath), path, args);
  va_end(args);

  psection = secfile_insert_base(secfile, fullpath, &ent_name);
  if (!psection) {
    return NULL;
  }

  if (allow_replace) {
    pentry = section_entry_by_name(psection, ent_name);
    if (NULL != pentry) {
      if (ENTRY_STR == entry_type(pentry)) {
        if (!entry_str_set(pentry, string)) {
          return NULL;
        }
      } else {
        entry_destroy(pentry);
        pentry = NULL;
      }
    }
  }

  if (NULL == pentry) {
    pentry = section_entry_str_new(psection, ent_name, string, TRUE);
  }

  if (NULL != pentry && NULL != comment) {
    entry_set_comment(pentry, comment);
  }

  return pentry;
}
