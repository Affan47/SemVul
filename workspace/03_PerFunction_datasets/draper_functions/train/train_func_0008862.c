drbd_thread_setup(void *arg)
{
	struct drbd_thread *thi = (struct drbd_thread *) arg;
	struct drbd_resource *resource = thi->resource;
	unsigned long flags;
	int retval;

	snprintf(current->comm, sizeof(current->comm), "drbd_%c_%s",
		 thi->name[0],
		 resource->name);

restart:
	retval = thi->function(thi);

	spin_lock_irqsave(&thi->t_lock, flags);


	if (thi->t_state == RESTARTING) {
		drbd_info(resource, "Restarting %s thread\n", thi->name);
		thi->t_state = RUNNING;
		spin_unlock_irqrestore(&thi->t_lock, flags);
		goto restart;
	}

	thi->task = NULL;
	thi->t_state = NONE;
	smp_mb();
	complete_all(&thi->stop);
	spin_unlock_irqrestore(&thi->t_lock, flags);

	drbd_info(resource, "Terminating %s\n", current->comm);


	if (thi->connection)
		kref_put(&thi->connection->kref, drbd_destroy_connection);
	kref_put(&resource->kref, drbd_destroy_resource);
	module_put(THIS_MODULE);
	return retval;
}
