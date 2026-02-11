vfio_group_get_device_fd(struct vfio_group *group, char *buf)
{
	struct vfio_device *device;
	struct file *filep;
	int ret;

	if (0 == atomic_read(&group->container_users) ||
	    !group->container->iommu_driver || !vfio_group_viable(group))
		return -EINVAL;

	device = vfio_device_get_from_name(group, buf);
	if (!device)
		return -ENODEV;

	ret = device->ops->open(device->device_data);
	if (ret) {
		vfio_device_put(device);
		return ret;
	}


	ret = get_unused_fd_flags(O_CLOEXEC);
	if (ret < 0) {
		device->ops->release(device->device_data);
		vfio_device_put(device);
		return ret;
	}

	filep = anon_inode_getfile("[vfio-device]", &vfio_device_fops,
				   device, O_RDWR);
	if (IS_ERR(filep)) {
		put_unused_fd(ret);
		ret = PTR_ERR(filep);
		device->ops->release(device->device_data);
		vfio_device_put(device);
		return ret;
	}


	filep->f_mode |= (FMODE_LSEEK | FMODE_PREAD | FMODE_PWRITE);

	atomic_inc(&group->container_users);

	fd_install(ret, filep);

	return ret;
}
