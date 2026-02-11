mailmessage_generic_flush(mailmessage * msg_info)
{
  struct generic_message_t * msg;

  if (msg_info->msg_mime != NULL) {
    mailmime_free(msg_info->msg_mime);
    msg_info->msg_mime = NULL;
  }
  msg = msg_info->msg_data;
  if (msg != NULL) {
    if (msg->msg_prefetch_free != NULL)
      msg->msg_prefetch_free(msg);
    msg->msg_fetched = 0;
  }
}
