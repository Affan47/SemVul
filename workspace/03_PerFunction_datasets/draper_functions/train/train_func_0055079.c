e820_pmem_probe(struct platform_device *pdev)
{
	static struct nvdimm_bus_descriptor nd_desc;
	struct device *dev = &pdev->dev;
	struct nvdimm_bus *nvdimm_bus;
	struct resource *p;

	nd_desc.attr_groups = e820_pmem_attribute_groups;
	nd_desc.provider_name = "e820";
	nvdimm_bus = nvdimm_bus_register(dev, &nd_desc);
	if (!nvdimm_bus)
		goto err;
	platform_set_drvdata(pdev, nvdimm_bus);

	for (p = iomem_resource.child; p ; p = p->sibling) {
		struct nd_region_desc ndr_desc;

		if (strncmp(p->name, "Persistent Memory (legacy)", 26) != 0)
			continue;

		memset(&ndr_desc, 0, sizeof(ndr_desc));
		ndr_desc.res = p;
		ndr_desc.attr_groups = e820_pmem_region_attribute_groups;
		ndr_desc.numa_node = e820_range_to_nid(p->start);
		set_bit(ND_REGION_PAGEMAP, &ndr_desc.flags);
		if (!nvdimm_pmem_region_create(nvdimm_bus, &ndr_desc))
			goto err;
	}

	return 0;

 err:
	nvdimm_bus_unregister(nvdimm_bus);
	dev_err(dev, "failed to register legacy persistent memory ranges\n");
	return -ENXIO;
}
