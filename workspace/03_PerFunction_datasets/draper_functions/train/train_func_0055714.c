csync_check_pure(const char *filename)
{
#ifdef __CYGWIN__


	if (!csync_lowercyg_disable)
		return 0;
#endif

	struct stat sbuf;
	int i=0;

	while (filename[i]) i++;

	{
		char myfilename[i+1];
		memcpy(myfilename, filename, i+1);
		while (1) {
			while (myfilename[i] != '/')
				if (--i <= 0) return 0;
			myfilename[i]=0;
			if ( lstat_strict(prefixsubst(myfilename), &sbuf) || S_ISLNK(sbuf.st_mode) ) return 1;
		}
	}
}
