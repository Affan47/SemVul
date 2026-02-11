mailpop3_msg_info_new(unsigned int indx, uint32_t size, char * uidl)
{
  struct mailpop3_msg_info * msg;

  msg = malloc(sizeof(* msg));
  if (msg == NULL)
    return NULL;
  msg->msg_index = indx;
  msg->msg_size = size;
  msg->msg_deleted = FALSE;
  msg->msg_uidl = uidl;

  return msg;
}
