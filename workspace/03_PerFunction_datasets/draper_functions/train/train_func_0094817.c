nd_pfn_probe(struct nd_namespace_common *ndns, void *drvdata)
{
	int rc;
	struct device *dev;
	struct nd_pfn *nd_pfn;
	struct nd_pfn_sb *pfn_sb;
	struct nd_region *nd_region = to_nd_region(ndns->dev.parent);

	if (ndns->force_raw)
		return -ENODEV;

	nvdimm_bus_lock(&ndns->dev);
	dev = __nd_pfn_create(nd_region, NULL, PFN_MODE_NONE, ndns);
	nvdimm_bus_unlock(&ndns->dev);
	if (!dev)
		return -ENOMEM;
	dev_set_drvdata(dev, drvdata);
	pfn_sb = kzalloc(sizeof(*pfn_sb), GFP_KERNEL);
	nd_pfn = to_nd_pfn(dev);
	nd_pfn->pfn_sb = pfn_sb;
	rc = nd_pfn_validate(nd_pfn);
	nd_pfn->pfn_sb = NULL;
	kfree(pfn_sb);
	dev_dbg(&ndns->dev, "%s: pfn: %s\n", __func__,
			rc == 0 ? dev_name(dev) : "<none>");
	if (rc < 0) {
		__nd_detach_ndns(dev, &nd_pfn->ndns);
		put_device(dev);
	} else
		__nd_device_register(&nd_pfn->dev);

	return rc;
}
