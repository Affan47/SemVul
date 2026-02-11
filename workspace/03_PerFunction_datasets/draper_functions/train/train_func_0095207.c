kfd_build_sysfs_node_tree(void)
{
	struct kfd_topology_device *dev;
	int ret;
	uint32_t i = 0;

	list_for_each_entry(dev, &topology_device_list, list) {
		ret = kfd_build_sysfs_node_entry(dev, i);
		if (ret < 0)
			return ret;
		i++;
	}

	return 0;
}
