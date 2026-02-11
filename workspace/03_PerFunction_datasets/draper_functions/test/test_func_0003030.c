mode_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct nd_pfn *nd_pfn = to_nd_pfn(dev);

	switch (nd_pfn->mode) {
	case PFN_MODE_RAM:
		return sprintf(buf, "ram\n");
	case PFN_MODE_PMEM:
		return sprintf(buf, "pmem\n");
	default:
		return sprintf(buf, "none\n");
	}
}
