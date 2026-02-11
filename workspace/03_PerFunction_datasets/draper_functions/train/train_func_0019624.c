start_process(pid_t *pid, void (*func)(void))
{
    pid_t child;

    switch(child = fork()) {
    case 0:
	(*func)();
	_exit(0);
    case -1:
        syswarn("cannot fork");
	return -1;
    default:
	*pid = child;
	return 0;
    }

}
