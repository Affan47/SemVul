mh_prefetch(mailmessage * msg_info)
{
  struct generic_message_t * msg;
  int r;
  char * msg_content;
  size_t msg_length;

  r = mhdriver_fetch_message(get_ancestor_session(msg_info),
      msg_info->msg_index, &msg_content, &msg_length);
  if (r != MAIL_NO_ERROR)
    return r;

  msg = msg_info->msg_data;

  msg->msg_message = msg_content;
  msg->msg_length = msg_length;

  return MAIL_NO_ERROR;
}
