smap_path(const char *homedir,
		       char **words)
{
	struct get_existing_folder_info gefi;
	char *n, *p;
	struct stat stat_buf;

	if ((n=smaptoUtf7(words)) == NULL)
		return NULL;

	p=maildir_name2dir(homedir, n);

	if (!p)
	{
		free(n);
		return NULL;
	}

	if (stat(p, &stat_buf) == 0)
	{
		free(p);
		return n;
	}

	gefi.fn=words;
	gefi.pathname=NULL;

	maildir_list(homedir ? homedir:".",
		     &get_existing_callback, &gefi);

	if (gefi.pathname)
	{
		free(n);
		free(p);

		return gefi.pathname;
	}

	free(p);
	return n;
}
