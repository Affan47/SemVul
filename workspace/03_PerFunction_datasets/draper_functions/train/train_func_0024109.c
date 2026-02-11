run_filter_dir(const char *filterdir,
			  const char *filename,
			  unsigned nmsgids,
			  std::string (*msgidfunc)(unsigned, void *),
			  void *funcarg)
{
	std::vector<std::string> filterlist;

	DIR	*dirp;
	struct dirent *de;
	std::string	sockname;
	int	rc;

	dirp=opendir(filterdir);

	while (dirp && (de=readdir(dirp)) != 0)
	{
		if (de->d_name[0] == '.')	continue;

		sockname=filterdir;
		sockname += "/";
		sockname += de->d_name;
		filterlist.push_back(sockname);
	}
	if (dirp)	closedir(dirp);

	std::sort(filterlist.begin(), filterlist.end());

	std::vector<std::string>::iterator b, e;

	for (b=filterlist.begin(), e=filterlist.end(); b != e; ++b)
	{
		rc = dofilter( *b, filename, nmsgids,
			       msgidfunc,
			       funcarg);

		if (rc)
			return rc;
	}
	return 0;
}
