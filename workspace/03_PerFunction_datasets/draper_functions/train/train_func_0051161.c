cavan_thread_recv_event_timeout(struct cavan_thread *thread, u32 *event, u32 ms)
{
	int ret;

	ret = poll(&thread->pfd, 1, ms);
	if (ret < 0)
	{
		pr_error_info("poll");
		return ret;
	}

	if (ret < 1)
	{
		return 0;
	}

	return cavan_thread_recv_event(thread, event);
}
