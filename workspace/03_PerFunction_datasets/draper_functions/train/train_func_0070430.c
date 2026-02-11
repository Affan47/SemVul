write_max_uid_value(mailsession * session)
{
  int r;
  char filename[PATH_MAX];
  FILE * f;
  int res;
  struct mh_cached_session_state_data * cached_data;
  struct mh_session_state_data * ancestor_data;
  int fd;

  MMAPString * mmapstr;
  size_t cur_token;

  cached_data = get_cached_data(session);
  ancestor_data = get_ancestor_data(session);

  if (cached_data->mh_quoted_mb == NULL)
    return MAIL_ERROR_BAD_STATE;

  snprintf(filename, PATH_MAX, "%s/%s/%s",
	   cached_data->mh_cache_directory,
	   cached_data->mh_quoted_mb, FILENAME_MAX_UID);

  fd = creat(filename, S_IRUSR | S_IWUSR);
  if (fd < 0) {
    res = MAIL_ERROR_FILE;
    goto err;
  }

  f = fdopen(fd, "w");
  if (f == NULL) {
    close(fd);
    res = MAIL_ERROR_FILE;
    goto err;
  }

  mmapstr = mmap_string_new("");
  if (mmapstr == NULL) {
    res = MAIL_ERROR_MEMORY;
    goto close;
  }

  r = mail_serialize_clear(mmapstr, &cur_token);
  if (r != MAIL_NO_ERROR) {
    res = r;
    goto free_mmapstr;
  }

  r = mailimf_cache_int_write(mmapstr, &cur_token,
      ancestor_data->mh_cur_folder->fl_max_index);
  if (r != MAIL_NO_ERROR) {
    res = r;
    goto free_mmapstr;
  }

  r = fwrite(mmapstr->str, 1, mmapstr->len, f);
  if ((size_t) r != mmapstr->len) {
    res = MAIL_ERROR_FILE;
    goto free_mmapstr;
  }

  mmap_string_free(mmapstr);
  fclose(f);

  return MAIL_NO_ERROR;

 free_mmapstr:
  mmap_string_free(mmapstr);
 close:
  fclose(f);
 err:
  return res;
}
