log_set_file(const char *subsys, const char *filename)
{
  struct LogDesc *desc;


  if (!(desc = log_find(subsys)))
    return 2;

  if (filename)
    desc->mark |= LOG_MARK_FILE;
  else
    desc->mark &= ~LOG_MARK_FILE;


  if (desc->file && desc->file->file && filename &&
      !strcmp(desc->file->file, filename))
    return 0;


  if (desc->subsys == LS_DEBUG)
    return log_debug_file(filename);

  if (desc->file)
    log_file_destroy(desc->file);


  desc->file = filename ? log_file_create(filename) : 0;

  return 0;
}
