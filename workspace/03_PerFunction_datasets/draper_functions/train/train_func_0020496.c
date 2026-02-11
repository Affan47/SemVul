bus_sort_breadthfirst(struct bus_type *bus,
			   int (*compare)(const struct device *a,
					  const struct device *b))
{
	LIST_HEAD(sorted_devices);
	struct list_head *pos, *tmp;
	struct klist_node *n;
	struct device_private *dev_prv;
	struct device *dev;
	struct klist *device_klist;

	device_klist = bus_get_device_klist(bus);

	spin_lock(&device_klist->k_lock);
	list_for_each_safe(pos, tmp, &device_klist->k_list) {
		n = container_of(pos, struct klist_node, n_node);
		dev_prv = to_device_private_bus(n);
		dev = dev_prv->device;
		device_insertion_sort_klist(dev, &sorted_devices, compare);
	}
	list_splice(&sorted_devices, &device_klist->k_list);
	spin_unlock(&device_klist->k_lock);
}
