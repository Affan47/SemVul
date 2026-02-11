fgettext_add_one_path(char *path, int position)
{
	char *dir,*domain;
	FGettextPath *tmp;

	if (!HaveNLSSupport)
	{
		return;
	}

	domain = GetQuotedString(path, &dir, ";", NULL, NULL, NULL);
	if (!dir || dir[0] == '\0' || dir[0] != '/')
	{
		if (dir)
		{
			free(dir);
		}
		CopyString(&dir, FGDefaultDir);
	}
	if (!domain || domain[0] == '\0')
	{
		domain = FGDefaultDomain;
	}

	tmp = (FGettextPath *)safemalloc(sizeof(FGettextPath));
	tmp->dir = dir;
	CopyString(&tmp->domain, domain);

	FGPathList = flist_insert_obj(FGPathList, tmp, position);
}
