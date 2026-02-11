mailimap_store_att_flags_send(mailstream * fd,
			      struct mailimap_store_att_flags * store_flags)
{
  int r;

  switch (store_flags->fl_sign) {
  case 1:
    r = mailimap_char_send(fd, '+');
    if (r != MAILIMAP_NO_ERROR)
      return r;
    break;
  case -1:
    r = mailimap_char_send(fd, '-');
    if (r != MAILIMAP_NO_ERROR)
      return r;
    break;
  }

  r = mailimap_token_send(fd, "FLAGS");
  if (r != MAILIMAP_NO_ERROR)
    return r;

  if (store_flags->fl_silent) {
    r = mailimap_token_send(fd, ".SILENT");
    if (r != MAILIMAP_NO_ERROR)
      return r;
  }

  r = mailimap_space_send(fd);
  if (r != MAILIMAP_NO_ERROR)
    return r;

  r = mailimap_flag_list_send(fd, store_flags->fl_flag_list);
  if (r != MAILIMAP_NO_ERROR)
    return r;

  return MAILIMAP_NO_ERROR;
}
