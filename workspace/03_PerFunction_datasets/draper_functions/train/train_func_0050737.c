hwdep_poll(struct snd_hwdep *hwdep, struct file *file,
			       poll_table *wait)
{
	struct snd_dg00x *dg00x = hwdep->private_data;
	unsigned int events;

	poll_wait(file, &dg00x->hwdep_wait, wait);

	spin_lock_irq(&dg00x->lock);
	if (dg00x->dev_lock_changed || dg00x->msg)
		events = POLLIN | POLLRDNORM;
	else
		events = 0;
	spin_unlock_irq(&dg00x->lock);

	return events;
}
