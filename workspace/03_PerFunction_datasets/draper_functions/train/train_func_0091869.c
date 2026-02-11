maildir_autoresponse_list(const char *maildir)
{
	char *d, **a;
	struct temp_autoresponse_list *list=NULL;
	unsigned list_cnt;
	struct temp_autoresponse_list *p;

	DIR *dirp;

	if (!maildir)
		maildir=".";

	d=malloc(strlen(maildir)+sizeof("/autoresponses"));

	if (!d)
		return (NULL);

	strcat(strcpy(d, maildir), "/autoresponses");

	dirp=opendir(d);
	free(d);

	list_cnt=0;

	if (dirp)
	{
		struct dirent *de;

		while ((de=readdir(dirp)) != NULL)
		{
			if (strchr(de->d_name, '.'))
				continue;

			p=(struct temp_autoresponse_list *)
				malloc(sizeof(struct temp_autoresponse_list));
			if (p)
			{
				if ((p->filename=strdup(de->d_name)) == NULL)
				{
					free(p);
					p=NULL;
				}
			}

			if (!p)
			{
				closedir(dirp);

				while (list)
				{
					p=list;
					list=p->next;
					free(p->filename);
					free(p);
				}
				return (NULL);
			}
			p->next=list;
			list=p;
			++list_cnt;
		}
		closedir(dirp);
	}

	a=malloc( (list_cnt+1)*sizeof(char *));

	if (!a)
	{
		while (list)
		{
			p=list;
			list=p->next;
			free(p->filename);
			free(p);
		}
		return (NULL);
	}

	list_cnt=0;

	while (list)
	{
		p=list;
		list=p->next;
		a[list_cnt]=p->filename;
		free(p);
		++list_cnt;
	}
	a[list_cnt]=0;
	return (a);
}
