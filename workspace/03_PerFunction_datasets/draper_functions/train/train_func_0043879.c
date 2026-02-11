fileAction(const char *fileName,
		struct stat *statbuf UNUSED_PARAM,
		void *userData,
		int depth UNUSED_PARAM)
{
	size_t len = strlen(fileName) - 4;
	char *scratch = userData;


	if (strcmp(fileName + len, "/dev") != 0 || len >= PATH_MAX)
		return FALSE;

	strcpy(scratch, fileName);
	scratch[len] = '\0';
	make_device( NULL, scratch, OP_add);

	return TRUE;
}
