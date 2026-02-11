maildir_aclt_del(maildir_aclt *aclt,
		     const char *del_strs,
		     const maildir_aclt *del_aclt)
{
	char *a, *b;

	if (del_aclt)
		del_strs= *del_aclt;

	if (!del_strs)
		return 0;

	if (!*aclt)
		return 0;

	for (a=b=*aclt; *a; a++)
	{
		if (strchr(del_strs, *a))
			continue;
		*b++= *a;
	}
	*b=0;

	if (**aclt == 0)
	{
		free(*aclt);
		*aclt=NULL;
	}
	return 0;
}
