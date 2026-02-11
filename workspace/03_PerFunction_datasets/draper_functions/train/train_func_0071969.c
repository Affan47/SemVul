error_state_write(struct file *file, struct kobject *kobj,
				 struct bin_attribute *attr, char *buf,
				 loff_t off, size_t count)
{
	struct device *kdev = kobj_to_dev(kobj);
	struct drm_minor *minor = dev_to_drm_minor(kdev);
	struct drm_device *dev = minor->dev;
	int ret;

	DRM_DEBUG_DRIVER("Resetting error state\n");

	ret = mutex_lock_interruptible(&dev->struct_mutex);
	if (ret)
		return ret;

	i915_destroy_error_state(dev);
	mutex_unlock(&dev->struct_mutex);

	return count;
}
