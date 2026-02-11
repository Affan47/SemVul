git_open_noatime(const char *name, struct packed_git *p)
{
	static int sha1_file_open_flag = O_NOATIME;

	for (;;) {
		int fd = open(name, O_RDONLY | sha1_file_open_flag);
		if (fd >= 0)
			return fd;


		if (errno == EMFILE) {
			if (unuse_one_window(p, -1))
				continue;
			else
				return -1;
		}


		if (errno != ENOENT && sha1_file_open_flag) {
			sha1_file_open_flag = 0;
			continue;
		}

		return -1;
	}
}
