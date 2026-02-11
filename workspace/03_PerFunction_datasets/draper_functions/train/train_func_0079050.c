walkdir(const char *path,
		void (*action) (const char *fname, bool isdir, int elevel),
		bool process_symlinks,
		int elevel)
{
	DIR		   *dir;
	struct dirent *de;

	dir = AllocateDir(path);
	if (dir == NULL)
	{
		ereport(elevel,
				(errcode_for_file_access(),
				 errmsg("could not open directory \"%s\": %m", path)));
		return;
	}

	while ((de = ReadDirExtended(dir, path, elevel)) != NULL)
	{
		char		subpath[MAXPGPATH];
		struct stat fst;
		int			sret;

		CHECK_FOR_INTERRUPTS();

		if (strcmp(de->d_name, ".") == 0 ||
			strcmp(de->d_name, "..") == 0)
			continue;

		snprintf(subpath, MAXPGPATH, "%s/%s", path, de->d_name);

		if (process_symlinks)
			sret = stat(subpath, &fst);
		else
			sret = lstat(subpath, &fst);

		if (sret < 0)
		{
			ereport(elevel,
					(errcode_for_file_access(),
					 errmsg("could not stat file \"%s\": %m", subpath)));
			continue;
		}

		if (S_ISREG(fst.st_mode))
			(*action) (subpath, false, elevel);
		else if (S_ISDIR(fst.st_mode))
			walkdir(subpath, action, false, elevel);
	}

	FreeDir(dir);


	(*action) (path, true, elevel);
}
