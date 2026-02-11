get_envelopes_list(mailsession * session,
    struct mailmessage_list * env_list)
{
  unsigned int i;
  char key[PATH_MAX];
  int r;
  struct mail_cache_db * maildb;
  int res;
  struct db_session_state_data * data;
  MMAPString * mmapstr;

  data = get_data(session);

  flags_store_process(session);

  r = mail_cache_db_open_lock(data->db_filename, &maildb);
  if (r < 0) {
    res = MAIL_ERROR_FILE;
    goto err;
  }

  mmapstr = mmap_string_new("");
  if (mmapstr == NULL) {
    res = MAIL_ERROR_MEMORY;
    goto close_db;
  }

  for(i = 0 ; i < carray_count(env_list->msg_tab) ; i ++) {
    mailmessage * msg;

    msg = carray_get(env_list->msg_tab, i);
    if (msg->msg_fields == NULL) {
      snprintf(key, sizeof(key), "%lu-envelope",
          (unsigned long) msg->msg_index);

      r = generic_cache_fields_read(maildb, mmapstr,
        key, &msg->msg_fields);
    }

    if (msg->msg_flags == NULL) {
      snprintf(key, sizeof(key), "%lu-flags",
          (unsigned long) msg->msg_index);

      r = generic_cache_flags_read(maildb, mmapstr,
          key, &msg->msg_flags);
    }
  }

  mmap_string_free(mmapstr);

  mail_cache_db_close_unlock(data->db_filename, maildb);

  return MAIL_NO_ERROR;

 close_db:
  mail_cache_db_close_unlock(data->db_filename, maildb);
 err:
  return res;
}
