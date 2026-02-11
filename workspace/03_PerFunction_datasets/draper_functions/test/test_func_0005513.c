append_message_flags(mailsession * session,
    const char * message, size_t size, struct mail_flags * flags)
{
  struct maildir * md;
  int r;
  char uid[PATH_MAX];
  struct maildir_msg * md_msg;
  chashdatum key;
  chashdatum value;
  uint32_t md_flags;
  struct mail_cache_db * cache_db_flags;
  char filename_flags[PATH_MAX];
  MMAPString * mmapstr;
  struct maildir_cached_session_state_data * data;

  md = get_maildir_session(session);
  if (md == NULL)
    return MAIL_ERROR_BAD_STATE;

  r = maildir_message_add_uid(md, message, size,
      uid, sizeof(uid));
  if (r != MAILDIR_NO_ERROR)
    return maildirdriver_maildir_error_to_mail_error(r);

  if (flags == NULL)
    goto exit;

  data = get_cached_data(session);

  snprintf(filename_flags, PATH_MAX, "%s%c%s%c%s",
      data->md_flags_directory, MAIL_DIR_SEPARATOR, data->md_quoted_mb,
      MAIL_DIR_SEPARATOR, FLAGS_NAME);

  r = mail_cache_db_open_lock(filename_flags, &cache_db_flags);
  if (r < 0)
    goto exit;

  mmapstr = mmap_string_new("");
  if (mmapstr == NULL)
    goto close_db_flags;

  r = write_cached_flags(cache_db_flags, mmapstr,
      uid, flags);

  mmap_string_free(mmapstr);
  mail_cache_db_close_unlock(filename_flags, cache_db_flags);

  if (r != MAIL_NO_ERROR)
    goto exit;

  key.data = uid;
  key.len = strlen(uid);
  r = chash_get(md->mdir_msg_hash, &key, &value);
  if (r < 0)
    goto exit;

  md_msg = value.data;

  md_flags = maildirdriver_flags_to_maildir_flags(flags->fl_flags);

  r = maildir_message_change_flags(md, uid, md_flags);
  if (r != MAILDIR_NO_ERROR)
    goto exit;

  return MAIL_NO_ERROR;

 close_db_flags:
  mail_cache_db_close_unlock(filename_flags, cache_db_flags);
 exit:
  return MAIL_NO_ERROR;
}
