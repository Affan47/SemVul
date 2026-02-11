enclosure_for_each_device(int (*fn)(struct enclosure_device *, void *),
			      void *data)
{
	int error = 0;
	struct enclosure_device *edev;

	mutex_lock(&container_list_lock);
	list_for_each_entry(edev, &container_list, node) {
		error = fn(edev, data);
		if (error)
			break;
	}
	mutex_unlock(&container_list_lock);

	return error;
}
