thread_create(const char *name, void (*thread) (void *data), void *data)
{
    pid_t pid;

    switch (pid = fork()) {
    case -1:
	error("fatal error: fork(%s) failed: %s", name, strerror(errno));
	return -1;
    case 0:
	info("thread %s starting...", name);
	if (thread_argc > 0) {
	    strncpy(thread_argv[0], name, strlen(thread_argv[0]));
	}
	thread(data);
	info("thread %s ended.", name);
	exit(0);
    default:
	info("forked process %d for thread %s", pid, name);
    }

    return pid;
}
