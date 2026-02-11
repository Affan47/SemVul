mkmode(mode_t mode)
{
	if (S_ISDIR(mode))
		return "drwxr-xr-x";
	else if (S_ISLNK(mode))
		return "lrwxrwxrwx";
	else if (S_ISGITLINK(mode))
		return "m---------";
	else if (S_ISREG(mode) && mode & S_IXUSR)
		return "-rwxr-xr-x";
	else if (S_ISREG(mode))
		return "-rw-r--r--";
	else
		return "----------";
}
