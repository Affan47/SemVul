secfile_lookup_plain_enum_full(const struct section_file *secfile,
                                    int *penumerator,
                                    secfile_enum_is_valid_fn_t is_valid_fn,
                                    secfile_enum_by_name_fn_t by_name_fn,
                                    const char *path, ...)
{
  char fullpath[MAX_LEN_SECPATH];
  const struct entry *pentry;
  const char *str;
  va_list args;

  SECFILE_RETURN_VAL_IF_FAIL(secfile, NULL, NULL != secfile, NULL);
  SECFILE_RETURN_VAL_IF_FAIL(secfile, NULL, NULL != penumerator, NULL);
  SECFILE_RETURN_VAL_IF_FAIL(secfile, NULL, NULL != is_valid_fn, NULL);
  SECFILE_RETURN_VAL_IF_FAIL(secfile, NULL, NULL != by_name_fn, NULL);

  va_start(args, path);
  fc_vsnprintf(fullpath, sizeof(fullpath), path, args);
  va_end(args);

  if (!(pentry = secfile_entry_by_path(secfile, fullpath))) {
    SECFILE_LOG(secfile, NULL, "\"%s\" entry doesn't exist.", fullpath);
    return FALSE;
  }

  if (!entry_str_get(pentry, &str)) {
    return FALSE;
  }

  *penumerator = by_name_fn(str, strcmp);
  if (is_valid_fn(*penumerator)) {
    return TRUE;
  }

  SECFILE_LOG(secfile, entry_section(pentry),
              "Entry \"%s\": no match for \"%s\".",
              entry_name(pentry), str);
  return FALSE;
}
