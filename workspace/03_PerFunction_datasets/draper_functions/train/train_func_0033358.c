pid_is_exec(pid_t pid)
{
	ssize_t bytes;
	char buf[sizeof("/proc/%u/cmdline") + sizeof(int)*3];

	sprintf(buf, "/proc/%u/cmdline", (unsigned)pid);
	bytes = open_read_close(buf, G.execname_cmpbuf, G.execname_sizeof);
	if (bytes > 0) {
		G.execname_cmpbuf[bytes] = '\0';
		return strcmp(execname, G.execname_cmpbuf) == 0;
	}
	return 0;
}
