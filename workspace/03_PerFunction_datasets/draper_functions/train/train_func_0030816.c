resolve_symlinks(char *path)
{
#ifdef HAVE_READLINK
	struct stat buf;
	char		orig_wd[MAXPGPATH],
				link_buf[MAXPGPATH];
	char	   *fname;


	if (!getcwd(orig_wd, MAXPGPATH))
	{
		log_error(_("could not identify current directory: %s"),
				  strerror(errno));
		return -1;
	}

	for (;;)
	{
		char	   *lsep;
		int			rllen;

		lsep = last_dir_separator(path);
		if (lsep)
		{
			*lsep = '\0';
			if (chdir(path) == -1)
			{
				log_error(_("could not change directory to \"%s\""), path);
				return -1;
			}
			fname = lsep + 1;
		}
		else
			fname = path;

		if (lstat(fname, &buf) < 0 ||
			!S_ISLNK(buf.st_mode))
			break;

		rllen = readlink(fname, link_buf, sizeof(link_buf));
		if (rllen < 0 || rllen >= sizeof(link_buf))
		{
			log_error(_("could not read symbolic link \"%s\""), fname);
			return -1;
		}
		link_buf[rllen] = '\0';
		strcpy(path, link_buf);
	}


	strcpy(link_buf, fname);

	if (!getcwd(path, MAXPGPATH))
	{
		log_error(_("could not identify current directory: %s"),
				  strerror(errno));
		return -1;
	}
	join_path_components(path, path, link_buf);
	canonicalize_path(path);

	if (chdir(orig_wd) == -1)
	{
		log_error(_("could not change directory to \"%s\""), orig_wd);
		return -1;
	}
#endif

	return 0;
}
