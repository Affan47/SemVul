nvdimm_namespace_attach_pfn(struct nd_namespace_common *ndns)
{
	struct nd_namespace_io *nsio = to_nd_namespace_io(&ndns->dev);
	struct nd_pfn *nd_pfn = to_nd_pfn(ndns->claim);
	struct device *dev = &nd_pfn->dev;
	struct vmem_altmap *altmap;
	struct nd_region *nd_region;
	struct nd_pfn_sb *pfn_sb;
	struct pmem_device *pmem;
	phys_addr_t offset;
	int rc;

	if (!nd_pfn->uuid || !nd_pfn->ndns)
		return -ENODEV;

	nd_region = to_nd_region(dev->parent);
	rc = nd_pfn_init(nd_pfn);
	if (rc)
		return rc;

	if (PAGE_SIZE != SZ_4K) {
		dev_err(dev, "only supported on systems with 4K PAGE_SIZE\n");
		return -ENXIO;
	}
	if (nsio->res.start & ND_PFN_MASK) {
		dev_err(dev, "%s not memory hotplug section aligned\n",
				dev_name(&ndns->dev));
		return -ENXIO;
	}

	pfn_sb = nd_pfn->pfn_sb;
	offset = le64_to_cpu(pfn_sb->dataoff);
	nd_pfn->mode = le32_to_cpu(nd_pfn->pfn_sb->mode);
	if (nd_pfn->mode == PFN_MODE_RAM) {
		if (offset != SZ_8K)
			return -EINVAL;
		nd_pfn->npfns = le64_to_cpu(pfn_sb->npfns);
		altmap = NULL;
	} else {
		rc = -ENXIO;
		goto err;
	}


	pmem = dev_get_drvdata(dev);
	devm_memunmap(dev, (void __force *) pmem->virt_addr);
	pmem->virt_addr = (void __pmem *) devm_memremap_pages(dev, &nsio->res);
	if (IS_ERR(pmem->virt_addr)) {
		rc = PTR_ERR(pmem->virt_addr);
		goto err;
	}


	pmem->data_offset = offset;
	rc = pmem_attach_disk(dev, ndns, pmem);
	if (rc)
		goto err;

	return rc;
 err:
	nvdimm_namespace_detach_pfn(ndns);
	return rc;
}
