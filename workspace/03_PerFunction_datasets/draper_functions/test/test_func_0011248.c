dlm_pthread_init(void)
{
    if (open_default_lockspace())
	return -1;

    if (default_ls->tid)
    {
	errno = EEXIST;
	return -1;
    }

    if (pthread_create(&default_ls->tid, NULL, dlm_recv_thread, default_ls))
    {
	int saved_errno = errno;
	close(default_ls->fd);
	free(default_ls);
	default_ls = NULL;
	errno = saved_errno;
	return -1;
    }
    return 0;
}
