slurm_allocation_msg_thr_destroy(
	allocation_msg_thread_t *arg)
{
	struct allocation_msg_thread *msg_thr =
		(struct allocation_msg_thread *)arg;
	if (msg_thr == NULL)
		return;

	debug2("slurm_allocation_msg_thr_destroy: clearing up message thread");
	eio_signal_shutdown(msg_thr->handle);
	pthread_join(msg_thr->id, NULL);
	eio_handle_destroy(msg_thr->handle);
	xfree(msg_thr);
}
