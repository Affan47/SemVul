filename_sans_dir(const char *fullfilename)
{
	int i, len = strlen(fullfilename);
	for (i = len - 1; i > -1; i--) {
		if (fullfilename[i] == '/') {
			return fullfilename + i + 1;
		}
	}
	return fullfilename;
}
