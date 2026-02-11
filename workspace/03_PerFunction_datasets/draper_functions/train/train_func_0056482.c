filter(const struct dirent *dir)
{
#if defined(__amd64__) || defined(__x86_64__) || defined(__powerpc64__)
	char* root = "/usr/lib64/";
#else
	char* root = "/usr/lib/";
#endif

#if defined (SOLARIS)


	char* testlib = "/libxpcom.so";
#else

	char* testlib = "/components/libwidget_gtk2.so";
#endif

	struct stat buf;
	int index = 0;
	char* dirname = (char *)dir->d_name;

	char* prefix = prefixes [index];
	while (prefix != NULL)
	{
		int prefixLength = strlen(prefix);
		if (strncmp(dirname, prefix, prefixLength) == 0)
		{


			if (index == XULRUNNER_INDEX) return 1;

			int dirLength = strlen(dirname);
			char* testpath = malloc (strlen(root) + dirLength + strlen(testlib) + 1);
			strcpy(testpath, root);
			strcat(testpath, dirname);
			strcat(testpath, testlib);
			int success = stat(testpath, &buf) == 0;
			free(testpath);
			if (success)
			{
				return 1;
			}
		}
		prefix = prefixes [++index];
	}
	return 0;
}
