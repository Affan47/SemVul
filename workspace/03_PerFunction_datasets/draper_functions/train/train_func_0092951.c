watchdog_open(struct inode *inode, struct file *filp)
{
	struct w83793_data *pos, *data = NULL;
	int watchdog_is_open;


	if (!mutex_trylock(&watchdog_data_mutex))
		return -ERESTARTSYS;
	list_for_each_entry(pos, &watchdog_data_list, list) {
		if (pos->watchdog_miscdev.minor == iminor(inode)) {
			data = pos;
			break;
		}
	}


	watchdog_is_open = test_and_set_bit(0, &data->watchdog_is_open);


	if (!watchdog_is_open)
		kref_get(&data->kref);

	mutex_unlock(&watchdog_data_mutex);


	if (watchdog_is_open)
		return -EBUSY;


	watchdog_enable(data);


	filp->private_data = data;

	return nonseekable_open(inode, filp);
}
