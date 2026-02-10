show_rev(struct device *dev, struct device_attribute *attr,
			char *buf)
{
	struct c4iw_dev *c4iw_dev = container_of(dev, struct c4iw_dev,
						 ibdev.dev);
	PDBG("%s dev 0x%p\n", __func__, dev);
	return sprintf(buf, "%d\n",
		       CHELSIO_CHIP_RELEASE(c4iw_dev->rdev.lldi.adapter_type));
}
