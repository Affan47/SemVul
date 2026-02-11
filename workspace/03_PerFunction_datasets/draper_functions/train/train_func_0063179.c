get_modprobe(void)
{
	int procfile;
	char *ret;

#define PROCFILE_BUFSIZ	1024
	procfile = open(PROC_SYS_MODPROBE, O_RDONLY);
	if (procfile < 0)
		return NULL;
	if (fcntl(procfile, F_SETFD, FD_CLOEXEC) == -1) {
		fprintf(stderr, "Could not set close on exec: %s\n",
			strerror(errno));
		exit(1);
	}

	ret = malloc(PROCFILE_BUFSIZ);
	if (ret) {
		memset(ret, 0, PROCFILE_BUFSIZ);
		switch (read(procfile, ret, PROCFILE_BUFSIZ)) {
		case -1: goto fail;
		case PROCFILE_BUFSIZ: goto fail;
		}
		if (ret[strlen(ret)-1]=='\n')
			ret[strlen(ret)-1]=0;
		close(procfile);
		return ret;
	}
 fail:
	free(ret);
	close(procfile);
	return NULL;
}
