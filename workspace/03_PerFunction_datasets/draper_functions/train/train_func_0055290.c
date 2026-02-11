calc_quota(struct maildir_autoresponse_quota *q, const char *maildir)
{
	char *p;
	DIR *dirp;
	struct dirent *de;

	q->files=0;
	q->bytes=0;

	if (!maildir)
		maildir=".";

	p=malloc(strlen(maildir)+sizeof("/autoresponses"));
	if (!p)
		return (-1);
	strcat(strcpy(p, maildir), "/autoresponses");
	dirp=opendir(p);
	free(p);
	if (!dirp)
		return (0);
	while ((de=readdir(dirp)) != 0)
	{
		if (strchr(de->d_name, '.'))
			continue;

		p=malloc(strlen(maildir)+strlen(de->d_name)
			 +sizeof("/autoresponses/"));
		if (!p)
		{
			closedir(dirp);
			return (-1);
		}

		strcat(strcat(strcpy(p, maildir), "/autoresponses/"),
		       de->d_name);
		add_quota(q, p, 1);
		free(p);
	}
	closedir(dirp);
	return (0);
}
