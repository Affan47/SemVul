vfio_group_nb_add_dev(struct vfio_group *group, struct device *dev)
{
	struct vfio_device *device;


	device = vfio_group_get_device(group, dev);
	if (WARN_ON_ONCE(device)) {
		vfio_device_put(device);
		return 0;
	}


	if (!atomic_read(&group->container_users))
		return 0;


	WARN(1, "Device %s added to live group %d!\n", dev_name(dev),
	     iommu_group_id(group->iommu_group));

	return 0;
}
