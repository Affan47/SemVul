available_slots_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct nvdimm_drvdata *ndd = dev_get_drvdata(dev);
	ssize_t rc;
	u32 nfree;

	if (!ndd)
		return -ENXIO;

	nvdimm_bus_lock(dev);
	nfree = nd_label_nfree(ndd);
	if (nfree - 1 > nfree) {
		dev_WARN_ONCE(dev, 1, "we ate our last label?\n");
		nfree = 0;
	} else
		nfree--;
	rc = sprintf(buf, "%d\n", nfree);
	nvdimm_bus_unlock(dev);
	return rc;
}
