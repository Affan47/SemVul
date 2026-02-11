shutdown_callback(pid_t pid)
{
	struct shutdown_callback *cb;

	cb = calloc(1, sizeof(*cb));
	if (!cb)
		return ENOMEM;

	INIT_LIST_HEAD(&cb->list);
	cb->pid = pid;
	log_debug(1, "adding %d for shutdown cb\n", pid);
	list_add_tail(&cb->list, &shutdown_callbacks);
	return 0;
}
