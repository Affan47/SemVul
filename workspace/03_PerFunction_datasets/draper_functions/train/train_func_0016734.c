pgstat_reset_remove_files(const char *directory)
{
	DIR		   *dir;
	struct dirent *entry;
	char		fname[MAXPGPATH];

	dir = AllocateDir(directory);
	while ((entry = ReadDir(dir, directory)) != NULL)
	{
		int			nchars;
		Oid			tmp_oid;


		if (strncmp(entry->d_name, "global.", 7) == 0)
			nchars = 7;
		else
		{
			nchars = 0;
			(void) sscanf(entry->d_name, "db_%u.%n",
						  &tmp_oid, &nchars);
			if (nchars <= 0)
				continue;

			if (strchr("0123456789", entry->d_name[3]) == NULL)
				continue;
		}

		if (strcmp(entry->d_name + nchars, "tmp") != 0 &&
			strcmp(entry->d_name + nchars, "stat") != 0)
			continue;

		snprintf(fname, MAXPGPATH, "%s/%s", directory,
				 entry->d_name);
		unlink(fname);
	}
	FreeDir(dir);
}
