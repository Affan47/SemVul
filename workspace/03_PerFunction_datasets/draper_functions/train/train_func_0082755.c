isert_device_get(struct rdma_cm_id *cma_id)
{
	struct isert_device *device;
	int ret;

	mutex_lock(&device_list_mutex);
	list_for_each_entry(device, &device_list, dev_node) {
		if (device->ib_device->node_guid == cma_id->device->node_guid) {
			device->refcount++;
			isert_info("Found iser device %p refcount %d\n",
				   device, device->refcount);
			mutex_unlock(&device_list_mutex);
			return device;
		}
	}

	device = kzalloc(sizeof(struct isert_device), GFP_KERNEL);
	if (!device) {
		mutex_unlock(&device_list_mutex);
		return ERR_PTR(-ENOMEM);
	}

	INIT_LIST_HEAD(&device->dev_node);

	device->ib_device = cma_id->device;
	ret = isert_create_device_ib_res(device);
	if (ret) {
		kfree(device);
		mutex_unlock(&device_list_mutex);
		return ERR_PTR(ret);
	}

	device->refcount++;
	list_add_tail(&device->dev_node, &device_list);
	isert_info("Created a new iser device %p refcount %d\n",
		   device, device->refcount);
	mutex_unlock(&device_list_mutex);

	return device;
}
