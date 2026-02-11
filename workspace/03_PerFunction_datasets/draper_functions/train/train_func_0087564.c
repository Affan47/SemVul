_hash_tools_lock_get (const char *cssfilename)
{
  char filename[MAX_FILENAME_LENGTH];
  char *pPeriod;
  int r;
  FILE* lockfile = NULL;

  if (cssfilename == NULL)
    return NULL;
  pPeriod = strrchr(cssfilename, '.');
  if (pPeriod == NULL || strcmp(pPeriod + 1, "css") || (size_t)(pPeriod - cssfilename + 5) >= sizeof(filename))
    return NULL;
  strncpy(filename, cssfilename, pPeriod - cssfilename + 1);
  strcpy(filename + (pPeriod - cssfilename + 1), "lock");
  _ds_prepare_path_for(filename);

  lockfile = fopen(filename, "a");
  if (lockfile == NULL) {
    LOG(LOG_ERR, ERR_IO_FILE_OPEN, filename, strerror(errno));
    return NULL;
  }
  r = _ds_get_fcntl_lock(fileno(lockfile));
  if (r) {
    fclose(lockfile);
	lockfile = NULL;
    LOG(LOG_ERR, ERR_IO_LOCK, filename, r, strerror(errno));
  }
  return lockfile;
}
