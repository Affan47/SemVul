nd_pmem_probe(struct device *dev)
{
	struct nd_region *nd_region = to_nd_region(dev->parent);
	struct nd_namespace_common *ndns;
	struct nd_namespace_io *nsio;
	struct pmem_device *pmem;

	ndns = nvdimm_namespace_common_probe(dev);
	if (IS_ERR(ndns))
		return PTR_ERR(ndns);

	nsio = to_nd_namespace_io(&ndns->dev);
	pmem = pmem_alloc(dev, &nsio->res, nd_region->id);
	if (IS_ERR(pmem))
		return PTR_ERR(pmem);

	pmem->ndns = ndns;
	dev_set_drvdata(dev, pmem);
	ndns->rw_bytes = pmem_rw_bytes;

	if (is_nd_btt(dev))
		return nvdimm_namespace_attach_btt(ndns);

	if (is_nd_pfn(dev))
		return nvdimm_namespace_attach_pfn(ndns);

	if (nd_btt_probe(ndns, pmem) == 0) {

		return -ENXIO;
	}

	if (nd_pfn_probe(ndns, pmem) == 0) {

		return -ENXIO;
	}

	return pmem_attach_disk(dev, ndns, pmem);
}
