auth_getuserinfo(const char *service, const char *uid,
		     int (*callback)(struct authinfo *, void *),
		     void *arg)
{
char    *buf=malloc(strlen(service)+strlen(uid)+20);
int     rc;

	if (!buf)
	{
		perror("malloc");
		return (1);
	}
	strcat(strcat(strcat(strcat(strcpy(buf, "PRE . "), service), " "),
		uid), "\n");

	rc=authdaemondo(buf, callback, arg);
	free(buf);
	return (rc);
}
