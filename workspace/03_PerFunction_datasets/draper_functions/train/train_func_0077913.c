l3_access_valid(struct drm_device *dev, loff_t offset)
{
	if (!HAS_L3_DPF(dev))
		return -EPERM;

	if (offset % 4 != 0)
		return -EINVAL;

	if (offset >= GEN7_L3LOG_SIZE)
		return -ENXIO;

	return 0;
}
