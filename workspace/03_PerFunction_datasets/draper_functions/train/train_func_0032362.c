to_bus_provider(struct device *dev)
{

	if (is_nd_pmem(dev) || is_nd_blk(dev)) {
		struct nvdimm_bus *nvdimm_bus = walk_to_nvdimm_bus(dev);

		return nvdimm_bus->module;
	}
	return NULL;
}
