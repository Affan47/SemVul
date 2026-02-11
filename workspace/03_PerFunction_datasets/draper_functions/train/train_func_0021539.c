maildir_acl_reset(const char *maildir)
{
	DIR *dirp;
	struct dirent *de;
	char *p;
	struct maildir_acl_resetList *rl=NULL;
	struct maildir_acl_resetList *r;
	time_t now;
	struct stat stat_buf;

	p=malloc(strlen(maildir) + sizeof("/" ACLHIERDIR));
	if (!p)
		return -1;

	strcat(strcpy(p, maildir), "/" ACLHIERDIR);

	dirp=opendir(p);

	if (!dirp)
	{
		mkdir(p, 0755);
		dirp=opendir(p);
	}
	free(p);

	while (dirp && (de=readdir(dirp)) != NULL)
	{
		if (de->d_name[0] == '.')
			continue;

		if ((r=malloc(sizeof(struct maildir_acl_resetList))) == NULL
		    || (r->mbox=strdup(de->d_name)) == NULL)
		{
			if (r)
				free(r);

			while (rl)
			{
				r=rl;
				rl=r->next;
				free(r->mbox);
				free(r);
			}
			closedir(dirp);
			return -1;
		}

		r->next=rl;
		rl=r;
	}
	if (dirp) closedir(dirp);

	maildir_list(maildir, acl_check_cb, &rl);

	time(&now);

	while (rl)
	{
		r=rl;
		rl=r->next;

		p=malloc(strlen(maildir)+strlen(r->mbox) +
			 sizeof("/" ACLHIERDIR "/"));
		if (p)
		{
			strcat(strcat(strcpy(p, maildir),
				      "/" ACLHIERDIR "/"), r->mbox);


			if (stat(p, &stat_buf) == 0 &&
			    stat_buf.st_mtime < now - 60*60)
				unlink(p);
			free(p);
		}
		free(r->mbox);
		free(r);
	}
	return 0;
}
