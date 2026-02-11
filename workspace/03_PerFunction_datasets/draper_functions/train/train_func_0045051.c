do_copy_message(unsigned long n, int byuid, void *voidptr)
{
	struct do_copy_info *cpy_info=(struct do_copy_info *)voidptr;
	int	fd;
	struct imapflags new_flags;

	--n;
	fd=imapscan_openfile(current_mailbox, &current_maildir_info, n);
	if (fd < 0)	return (0);
	get_message_flags(current_maildir_info.msgs+n, 0, &new_flags);

	if (copy_message(fd, cpy_info, &new_flags,

			 acl_flags_adjust(cpy_info->acls,
					  &new_flags) ? NULL
			 : current_maildir_info.msgs[n].keywordMsg,
			 current_maildir_info.msgs[n].uid))
	{
		close(fd);
		return (-1);
	}
	close(fd);
	current_maildir_info.msgs[n].copiedflag=1;
	return (0);
}
