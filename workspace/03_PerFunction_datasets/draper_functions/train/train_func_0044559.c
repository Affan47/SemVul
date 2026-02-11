is_directory(const char *fileName, int followLinks, struct stat *statBuf)
{
	int status;
	struct stat astatBuf;

	if (statBuf == NULL) {

		statBuf = &astatBuf;
	}

	if (followLinks)
		status = stat(fileName, statBuf);
	else
		status = lstat(fileName, statBuf);

	status = (status == 0 && S_ISDIR(statBuf->st_mode));

	return status;
}
