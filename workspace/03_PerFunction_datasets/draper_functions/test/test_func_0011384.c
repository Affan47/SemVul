mail_flags_remove_extension(struct mail_flags * flags,
				char * ext_flag)
{
  clistiter * cur;

  cur = clist_begin(flags->fl_extension);
  while (cur != NULL) {
    char * flag_name;

    flag_name = clist_content(cur);

    if (strcasecmp(flag_name, ext_flag) == 0) {
      free(flag_name);
      cur = clist_delete(flags->fl_extension, cur);
    }
    else
      cur = clist_next(cur);
  }

  return MAIL_NO_ERROR;
}
