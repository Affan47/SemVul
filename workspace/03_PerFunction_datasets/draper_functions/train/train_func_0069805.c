pollset_alloc(struct pollset **new)
{
	struct pollset *pset;
	int ret;

	*new=NULL;
	pset=g_slice_new0(struct pollset);
	ret=selfpipe_create(&pset->wakeup);
	if (ret) {
		g_slice_free(struct pollset, pset);
		return ret;
	}
	pthread_mutex_init(&pset->lock, NULL);
	pthread_mutex_init(&pset->poll_lock, NULL);
	pthread_cond_init(&pset->serial_cond, NULL);
	pset->running_serial=NOT_RUNNING;
	pset->members=g_hash_table_new_full(g_int_hash, g_int_equal, NULL,
				(GDestroyNotify)poll_fd_free);
	pset->dead=g_queue_new();
	pset->timers=g_tree_new(timeval_compare);
	pset->expired=g_queue_new();
	pset->ops = ops_epoll ?: ops_poll;
again:
	ret=pset->ops->create(pset);
	if (ret == ENOSYS && pset->ops == ops_epoll) {
		pset->ops=ops_poll;
		goto again;
	} else if (ret) {
		goto cleanup;
	}
	ret=pollset_add(pset, selfpipe_fd(pset->wakeup), POLLSET_READABLE,
				NULL, NULL, NULL, NULL, assert_callback_func,
				NULL);
	if (ret) {
		pset->ops->destroy(pset);
		goto cleanup;
	}
	*new=pset;
	return 0;

cleanup:
	g_hash_table_destroy(pset->members);
	g_queue_free(pset->dead);
	selfpipe_destroy(pset->wakeup);
	g_slice_free(struct pollset, pset);
	return ret;
}
