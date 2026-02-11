most_stop_channel(struct most_interface *iface, int id,
		      struct most_aim *aim)
{
	struct most_c_obj *c;

	if (unlikely((!iface) || (id >= iface->num_channels) || (id < 0))) {
		pr_err("Bad interface or index out of range\n");
		return -EINVAL;
	}
	c = get_channel_by_iface(iface, id);
	if (unlikely(!c))
		return -EINVAL;

	mutex_lock(&c->start_mutex);
	if (c->aim0.refs + c->aim1.refs >= 2)
		goto out;

	mutex_lock(&c->stop_task_mutex);
	if (c->hdm_enqueue_task)
		kthread_stop(c->hdm_enqueue_task);
	c->hdm_enqueue_task = NULL;
	mutex_unlock(&c->stop_task_mutex);

	mutex_lock(&deregister_mutex);
	if (atomic_read(&c->inst->tainted)) {
		mutex_unlock(&deregister_mutex);
		mutex_unlock(&c->start_mutex);
		return -ENODEV;
	}
	mutex_unlock(&deregister_mutex);

	if (iface->mod && modref) {
		module_put(iface->mod);
		modref--;
	}

	c->is_poisoned = true;
	if (c->iface->poison_channel(c->iface, c->channel_id)) {
		pr_err("Cannot stop channel %d of mdev %s\n", c->channel_id,
		       c->iface->description);
		mutex_unlock(&c->start_mutex);
		return -EAGAIN;
	}
	flush_trash_fifo(c);
	flush_channel_fifos(c);

#ifdef CMPL_INTERRUPTIBLE
	if (wait_for_completion_interruptible(&c->cleanup)) {
		pr_info("Interrupted while clean up ch %d\n", c->channel_id);
		mutex_unlock(&c->start_mutex);
		return -EINTR;
	}
#else
	wait_for_completion(&c->cleanup);
#endif
	c->is_poisoned = false;

out:
	if (aim == c->aim0.ptr)
		c->aim0.refs--;
	if (aim == c->aim1.ptr)
		c->aim1.refs--;
	mutex_unlock(&c->start_mutex);
	return 0;
}
