_step_suspend_write(int fd)
{
	int req = REQUEST_STEP_SUSPEND;

	safe_write(fd, &req, sizeof(int));
	return 0;
rwfail:
	return -1;
}
