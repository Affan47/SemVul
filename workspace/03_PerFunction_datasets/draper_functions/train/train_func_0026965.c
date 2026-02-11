_ds_ff_pref_commit (
  const char *filename,
  FILE *out_file)
{
  char backup[MAX_FILENAME_LENGTH];

  snprintf(backup, sizeof(backup), "%s.bak", filename);
  if (fclose(out_file)) {
    LOG(LOG_ERR, ERR_IO_FILE_CLOSE, backup, strerror(errno));
    return EFAILURE;
  }

  if (rename(backup, filename)) {
    LOG(LOG_ERR, ERR_IO_FILE_RENAME, backup, strerror(errno));
    unlink(backup);
    return EFAILURE;
  }

  return 0;
}
