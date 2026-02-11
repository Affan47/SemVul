shut_down_worker(struct work_queue *q, struct work_queue_worker *w)
{
	if(!w)
		return 0;

	send_worker_msg(w, "%s\n", time(0) + short_timeout, "exit");
	remove_worker(q, w);
	return 1;
}
