vfio_del_group_dev(struct device *dev)
{
	struct vfio_device *device = dev_get_drvdata(dev);
	struct vfio_group *group = device->group;
	void *device_data = device->device_data;
	struct vfio_unbound_dev *unbound;
	unsigned int i = 0;
	long ret;
	bool interrupted = false;


	vfio_group_get(group);


	unbound = kzalloc(sizeof(*unbound), GFP_KERNEL);
	if (unbound) {
		unbound->dev = dev;
		mutex_lock(&group->unbound_lock);
		list_add(&unbound->unbound_next, &group->unbound_list);
		mutex_unlock(&group->unbound_lock);
	}
	WARN_ON(!unbound);

	vfio_device_put(device);


	do {
		device = vfio_group_get_device(group, dev);
		if (!device)
			break;

		if (device->ops->request)
			device->ops->request(device_data, i++);

		vfio_device_put(device);

		if (interrupted) {
			ret = wait_event_timeout(vfio.release_q,
					!vfio_dev_present(group, dev), HZ * 10);
		} else {
			ret = wait_event_interruptible_timeout(vfio.release_q,
					!vfio_dev_present(group, dev), HZ * 10);
			if (ret == -ERESTARTSYS) {
				interrupted = true;
				dev_warn(dev,
					 "Device is currently in use, task"
					 " \"%s\" (%d) "
					 "blocked until device is released",
					 current->comm, task_pid_nr(current));
			}
		}
	} while (ret <= 0);

	vfio_group_put(group);

	return device_data;
}
