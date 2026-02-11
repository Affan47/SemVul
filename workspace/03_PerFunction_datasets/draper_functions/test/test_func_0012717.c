mailimf_cache_group_write(MMAPString * mmapstr, size_t * indx,
				     struct mailimf_group * group)
{
  int r;

  r = mailimf_cache_string_write(mmapstr, indx, group->grp_display_name,
			   strlen(group->grp_display_name));
  if (r != MAIL_NO_ERROR)
    return r;

  r = mailimf_cache_mailbox_list_write(mmapstr, indx, group->grp_mb_list);
  if (r != MAIL_NO_ERROR)
    return r;

  return MAIL_NO_ERROR;
}
