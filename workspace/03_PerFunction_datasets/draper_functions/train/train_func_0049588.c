pop3_prefetch(mailmessage * msg_info)
{
  char * msg_content;
  size_t msg_length;
  struct generic_message_t * msg;
  int r;
  struct pop3_cached_session_state_data * cached_data;
  char filename[PATH_MAX];


  cached_data = get_cached_session_data(msg_info);

  snprintf(filename, PATH_MAX, "%s/%s",
	   cached_data->pop3_cache_directory, msg_info->msg_uid);

  r = generic_cache_read(filename, &msg_content, &msg_length);
  if (r == MAIL_NO_ERROR) {
    msg = msg_info->msg_data;

    msg->msg_message = msg_content;
    msg->msg_length = msg_length;

    return MAIL_NO_ERROR;
  }


  r = pop3driver_retr(get_ancestor_session(msg_info), msg_info->msg_index,
		      &msg_content, &msg_length);
  if (r != MAIL_NO_ERROR)
    return r;


  generic_cache_store(filename, msg_content, msg_length);

  msg = msg_info->msg_data;

  msg->msg_message = msg_content;
  msg->msg_length = msg_length;

  return MAIL_NO_ERROR;
}
