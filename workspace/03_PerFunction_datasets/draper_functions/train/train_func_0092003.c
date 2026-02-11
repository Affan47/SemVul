mailpop3_msg_info_tab_find_msg(carray * msg_tab, unsigned int indx)
{
  struct mailpop3_msg_info * msg;

  if (indx == 0)
    return NULL;

  if (indx > carray_count(msg_tab))
    return NULL;

  msg = carray_get(msg_tab, indx - 1);

  return msg;
}
