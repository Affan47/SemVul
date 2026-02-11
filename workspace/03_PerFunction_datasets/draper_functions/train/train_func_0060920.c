xreadlink(const char *path)
{
	static const int GROWBY = 80;

	char *buf = NULL;
	int bufsize = 0, readsize = 0;

	do {
		buf = xrealloc(buf, bufsize += GROWBY);
		readsize = readlink(path, buf, bufsize);
		if (readsize == -1) {
			perror_msg_and_die("%s:%s", app_name, path);
		}
	}
	while (bufsize < readsize + 1);

	buf[readsize] = '\0';
	return buf;
}
