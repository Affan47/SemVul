sigchld_consumer(void *arg) {
    int n;
    char buf[sizeof(pid_t)];
    pid_t pid;

    while (1) {
	n=read(sigchld_pipe_rd, buf, sizeof(pid_t));
	if (n==0)
	    break;
	else if(n==-1) {
	    if (errno == EINTR)
		continue;
	    else
		break;
	} else if (n != sizeof(pid_t))
	    break;
	memcpy(&pid, buf, sizeof(pid_t));
	sigchld_process(pid);
    }

    if (n != 0)
	fprintf(stderr,
		"Netsys: sigchld_consumer thread terminates after error\n");

    return NULL;
}
