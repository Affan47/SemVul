callback_userid(struct userid_callback *a, void *vp)
{
	struct userid_info *uinfo=(struct userid_info *)vp;
	char *u=strdup(a->userid);
	struct stat stat_buf;

	if (!u)
		return (-1);

	if (stat(a->homedir, &stat_buf) < 0)
	{
		free(u);
		return (-1);
	}

	if (stat_buf.st_mode & S_ISVTX)
	{
		free(u);
		errno=EAGAIN;
		return (1);
	}

	uinfo->userid=u;
	return (0);
}
