prefetch(mailmessage * msg_info)
{
  struct generic_message_t * msg;
  int res;
  struct db_msg_data * data;
  struct db_session_state_data * sess_data;
  MMAPString * msg_content;
  struct mail_cache_db * maildb;
  int r;
  char key[PATH_MAX];
  void * msg_data;
  size_t msg_data_len;

  sess_data = get_session_data(msg_info);

  r = mail_cache_db_open_lock(sess_data->db_filename, &maildb);
  if (r < 0) {
    res = MAIL_ERROR_FILE;
    goto err;
  }

  snprintf(key, sizeof(key), "%lu", (unsigned long) msg_info->msg_index);
  r = mail_cache_db_get(maildb, key, strlen(key), &msg_data, &msg_data_len);
  if (r < 0) {
    res = MAIL_ERROR_MSG_NOT_FOUND;
    goto close_db;
  }

  msg_content = mmap_string_new_len(msg_data, msg_data_len);
  if (msg_content == NULL) {
    res = MAIL_ERROR_MEMORY;
    goto close_db;
  }

  data = malloc(sizeof(* data));
  if (data == NULL) {
    res = MAIL_ERROR_MEMORY;
    goto free_mmapstr;
  }

  data->msg_content = msg_content;

  msg = msg_info->msg_data;

  msg->msg_data = data;
  msg->msg_message = msg_content->str;
  msg->msg_length = msg_content->len;

  mail_cache_db_close_unlock(sess_data->db_filename, maildb);

  return MAIL_NO_ERROR;

 free_mmapstr:
  mmap_string_free(msg_content);
 close_db:
  mail_cache_db_close_unlock(sess_data->db_filename, maildb);
 err:
  return res;
}
