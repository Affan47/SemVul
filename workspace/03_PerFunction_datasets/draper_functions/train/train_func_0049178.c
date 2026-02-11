git_open_noatime(const char *name)
{
	static int sha1_file_open_flag = O_NOATIME;

	for (;;) {
		int fd = open(name, O_RDONLY | sha1_file_open_flag);
		if (fd >= 0)
			return fd;


		if (errno != ENOENT && sha1_file_open_flag) {
			sha1_file_open_flag = 0;
			continue;
		}

		return -1;
	}
}
