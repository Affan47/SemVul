hwdep_poll(struct snd_hwdep *hwdep, struct file *file, poll_table *wait)
{
	struct snd_efw *efw = hwdep->private_data;
	unsigned int events;

	poll_wait(file, &efw->hwdep_wait, wait);

	spin_lock_irq(&efw->lock);
	if (efw->dev_lock_changed || efw->pull_ptr != efw->push_ptr)
		events = POLLIN | POLLRDNORM;
	else
		events = 0;
	spin_unlock_irq(&efw->lock);

	return events | POLLOUT;
}
