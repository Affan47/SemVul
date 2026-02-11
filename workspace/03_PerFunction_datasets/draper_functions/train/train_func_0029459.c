auth_pipe_pre(const char *uid, const char *service,
		int (*callback)(struct authinfo *, void *),
		void *arg)
{
	char *buf;
	int rdfd, wrfd, rc;

	if (disabled_flag)
		return -1;

	buf=malloc(strlen(service)+strlen(uid)+20);
	if (!buf)
		return 1;

	strcat(strcat(strcat(strcat(strcpy(buf, "PRE . "), service), " "),
		uid), "\n");

	if (getPipe(&rdfd, &wrfd))
	{
		free(buf);
		return 1;
	}
	rc=_authdaemondo(wrfd, rdfd, buf, callback, arg);
	free(buf);
	if (rc > 0) closePipe();
	return (rc);
}
