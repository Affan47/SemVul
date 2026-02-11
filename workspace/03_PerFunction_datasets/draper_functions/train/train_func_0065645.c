conn_set_free(struct mrpc_conn_set *set)
{
	selfpipe_set(set->events_notify_pipe);
	pthread_mutex_lock(&set->events_lock);
	while (set->events_threads)
		pthread_cond_wait(&set->events_threads_cond, &set->events_lock);
	pthread_mutex_unlock(&set->events_lock);
	pollset_free(set->pollset);
	selfpipe_destroy(set->events_notify_pipe);
	selfpipe_destroy(set->shutdown_pipe);
	g_async_queue_unref(set->listeners);
	g_queue_free(set->event_conns);
	g_free(set->trashbuf);
	g_slice_free(struct mrpc_conn_set, set);
}
