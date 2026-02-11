secfile_insert_str_vec_full(struct section_file *secfile,
                                   const char *const *strings, size_t dim,
                                   const char *comment, bool allow_replace,
                                   bool no_escape, const char *path, ...)
{
  char fullpath[MAX_LEN_SECPATH];
  size_t i, ret = 0;
  va_list args;

  SECFILE_RETURN_VAL_IF_FAIL(secfile, NULL, NULL != secfile, 0);

  va_start(args, path);
  fc_vsnprintf(fullpath, sizeof(fullpath), path, args);
  va_end(args);


  if (dim > 0
      && NULL != secfile_insert_str_full(secfile, strings[0], comment,
                                         allow_replace, no_escape,
                                         "%s", fullpath)) {
    ret++;
  }
  for (i = 1; i < dim; i++) {
    if (NULL != secfile_insert_str_full(secfile, strings[i], comment,
                                        allow_replace, no_escape,
                                        "%s,%d", fullpath, (int) i)) {
      ret++;
    }
  }

  return ret;
}
