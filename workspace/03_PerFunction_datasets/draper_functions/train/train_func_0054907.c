mailimap_append_send(mailstream * fd,
			 const char * mailbox,
			 struct mailimap_flag_list * flag_list,
			 struct mailimap_date_time * date_time,
			 size_t literal_size)
{
  int r;

  r = mailimap_token_send(fd, "APPEND");
  if (r != MAILIMAP_NO_ERROR)
    return r;
  r = mailimap_space_send(fd);
  if (r != MAILIMAP_NO_ERROR)
    return r;
  r = mailimap_mailbox_send(fd, mailbox);
  if (r != MAILIMAP_NO_ERROR)
    return r;
  if (flag_list != NULL) {
    r = mailimap_space_send(fd);
    if (r != MAILIMAP_NO_ERROR)
      return r;
    r = mailimap_flag_list_send(fd, flag_list);
    if (r != MAILIMAP_NO_ERROR)
      return r;
  }
  if (date_time != NULL) {
    r = mailimap_space_send(fd);
    if (r != MAILIMAP_NO_ERROR)
      return r;
    r = mailimap_date_time_send(fd, date_time);
    if (r != MAILIMAP_NO_ERROR)
      return r;
  }

  r = mailimap_space_send(fd);
  if (r != MAILIMAP_NO_ERROR)
    return r;
  r = mailimap_literal_count_send(fd, literal_size);
  if (r != MAILIMAP_NO_ERROR)
    return r;

  return MAILIMAP_NO_ERROR;
}
