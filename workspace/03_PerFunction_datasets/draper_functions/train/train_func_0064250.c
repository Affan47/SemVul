debugger_dump(void)
{
    pid_t tf_pid = getpid();

    const char *exename;

    if ((exename = get_exename(tf_pid))) {
	pid_t child_pid;
	child_pid = fork();
	if (child_pid < 0) {

	    fprintf(stderr, "fork: %s\r\n", strerror(errno));
	} else if (child_pid > 0) {

	    pid_t wait_pid = 0;
	    int status = 0;
	    wait_pid = waitpid(child_pid, &status, 0);
	    if (shell_status(status) == 0) {
		return 1;
	    } else {
		unlink(dumpname);
	    }
	} else {

	    char inname[1024];
	    char cmd[2048];
	    int retval;
	    sprintf(inname, "%.1000s/tf.gdb", TFLIBDIR);
	    sprintf(cmd, "chmod go-rwx %s; gdb -n -batch -x %s '%s' %d "
		">>%s 2>&1", dumpname, inname, exename, tf_pid, dumpname);
	    retval = system(cmd);
	    exit(shell_status(retval) == 0 ? 0 : 1);
	}
    }
    return 0;
}
