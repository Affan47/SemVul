rinoo_channel_read(t_channel *channel, void *dest, size_t size)
{
	t_task *task;
	t_sched *sched;

	sched = rinoo_sched_self();
	if (channel->sched != sched) {
		return -1;
	}
	if (channel->buf == NULL) {
		channel->task = rinoo_task_self();
		rinoo_task_release(sched);
		if (channel->buf == NULL) {
			return -1;
		}
	}
	if (size > channel->size) {
		size = channel->size;
	}
	memcpy(dest, channel->buf, size);
	channel->size -= size;
	if (channel->size > 0) {
		channel->buf += size;
	} else {
		task = channel->task;
		channel->buf = NULL;
		channel->size = 0;
		channel->task = NULL;
		rinoo_task_schedule(task, NULL);
	}
	return size;
}
