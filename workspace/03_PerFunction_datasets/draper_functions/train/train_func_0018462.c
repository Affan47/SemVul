get_message_length(const char *pattern, char *arg[], int narg)
{
	int len;
	int i;

	len = strlen(pattern) + narg;
	for (i = 0; i < narg; i++)
		len += strlen(arg[i]);

	if (!EXEC_debug)
		len -= narg * 3;

	return len;
}
