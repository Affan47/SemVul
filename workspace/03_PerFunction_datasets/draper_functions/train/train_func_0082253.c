mailimap_mailbox_data_list_parse(mailstream * fd, MMAPString * buffer,
				 size_t * indx,
				 struct mailimap_mailbox_list ** result,
				 size_t progr_rate,
				 progress_function * progr_fun)
{
  size_t cur_token;
  struct mailimap_mailbox_list * mb_list;
  int r;
  int res;

  cur_token = * indx;

  r = mailimap_token_case_insensitive_parse(fd, buffer, &cur_token, "LIST");
  if (r != MAILIMAP_NO_ERROR) {
    res = r;
    return r;
  }

  r = mailimap_space_parse(fd, buffer, &cur_token);
  if (r != MAILIMAP_NO_ERROR) {
    res = r;
    return r;
  }

  r = mailimap_mailbox_list_parse(fd, buffer, &cur_token, &mb_list,
				  progr_rate, progr_fun);
  if (r != MAILIMAP_NO_ERROR) {
    res = r;
    return r;
  }

  * result = mb_list;
  * indx = cur_token;

  return MAILIMAP_NO_ERROR;
}
