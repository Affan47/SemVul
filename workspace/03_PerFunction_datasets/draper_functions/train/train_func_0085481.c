imap_fetch_envelope(mailmessage * msg_info,
			       struct mailimf_fields ** result)
{
  struct mailimf_fields * fields;
  int r;
  struct mail_cache_db * cache_db;
  MMAPString * mmapstr;
  char filename[PATH_MAX];
  struct imap_cached_session_state_data * data;
  int res;

  data = get_cached_session_data(msg_info);
  if (data->imap_quoted_mb == NULL) {
    res = MAIL_ERROR_BAD_STATE;
    goto err;
  }

  snprintf(filename, PATH_MAX, "%s/%s", data->imap_quoted_mb, ENV_NAME);

  r = mail_cache_db_open_lock(filename, &cache_db);
  if (r < 0) {
    res = MAIL_ERROR_FILE;
    goto err;
  }

  mmapstr = mmap_string_new("");
  if (mmapstr == NULL) {
    res = MAIL_ERROR_MEMORY;
    goto close_db;
  }

  r = imapdriver_get_cached_envelope(cache_db, mmapstr,
      msg_info->msg_session, msg_info, &fields);

  if ((r != MAIL_ERROR_CACHE_MISS) && (r != MAIL_NO_ERROR)) {
    res = r;
    goto close_db;
  }

  r = mailmessage_fetch_envelope(get_ancestor(msg_info), &fields);
  if (r != MAIL_NO_ERROR) {
    res = r;
    goto close_db;
  }

  r = imapdriver_write_cached_envelope(cache_db, mmapstr,
      msg_info->msg_session, msg_info, fields);

  * result = fields;

  mmap_string_free(mmapstr);
  mail_cache_db_close_unlock(filename, cache_db);

  return MAIL_NO_ERROR;

 close_db:
  mail_cache_db_close_unlock(filename, cache_db);
 err:
  return res;
}
