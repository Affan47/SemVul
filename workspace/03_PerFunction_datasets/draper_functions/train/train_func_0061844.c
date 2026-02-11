vfio_fops_mmap(struct file *filep, struct vm_area_struct *vma)
{
	struct vfio_container *container = filep->private_data;
	struct vfio_iommu_driver *driver;
	int ret = -EINVAL;

	down_read(&container->group_lock);

	driver = container->iommu_driver;
	if (likely(driver && driver->ops->mmap))
		ret = driver->ops->mmap(container->iommu_data, vma);

	up_read(&container->group_lock);

	return ret;
}
