getCWD()
{
	char	*cwd;
	char	pathname[FILESIZE];

#ifndef MAC
	cwd = getenv("CWD");
	if (cwd == NULL || !chkCWD(cwd)) {
		cwd = getenv("PWD");
		if (cwd == NULL || !chkCWD(cwd)) {
#endif
			cwd = getcwd(pathname, sizeof(pathname));
			if (cwd == NULL)
				error("Cannot get current directory");
#ifndef MAC
		}
	}
#endif
#ifdef MSFILESYSTEM
	cwd = fixpath(cwd);
#endif
	setCWD(cwd);
}
