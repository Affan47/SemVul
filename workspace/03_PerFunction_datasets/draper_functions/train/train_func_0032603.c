sigCLD(int)
{
    int old_errno = errno;
    pid_t pid;
    int status;

    while ((pid = waitpid(-1, &status, WNOHANG)) > 0)
	Dispatcher::instance()._cqueue->setStatus(pid, status);
    errno = old_errno;
}
