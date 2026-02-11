_slurm_cgroup_is_pid_a_slurm_task(uint64_t id, pid_t pid)
{
	int fstatus = -1;
	int fd;
	pid_t ppid;
	char file_path[PATH_MAX], buf[2048];

	if (snprintf(file_path, PATH_MAX, "/proc/%ld/stat",
		     (long)pid) >= PATH_MAX) {
		debug2("unable to build pid '%d' stat file: %m ", pid);
		return fstatus;
	}

	if ((fd = open(file_path, O_RDONLY)) < 0) {
		debug2("unable to open '%s' : %m ", file_path);
		return fstatus;
	}
	if (read(fd, buf, 2048) <= 0) {
		debug2("unable to read '%s' : %m ", file_path);
		close(fd);
		return fstatus;
	}
	close(fd);

	if (sscanf(buf, "%*d %*s %*s %d", &ppid) != 1) {
		debug2("unable to get ppid of pid '%d', %m", pid);
		return fstatus;
	}


	if (ppid == (pid_t) id)
		fstatus = 1;
	else
		fstatus = 0;

	return fstatus;
}
