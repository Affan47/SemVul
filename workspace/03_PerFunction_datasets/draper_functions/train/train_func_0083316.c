nvdimm_bus_probe_end(struct nvdimm_bus *nvdimm_bus)
{
	nvdimm_bus_lock(&nvdimm_bus->dev);
	if (--nvdimm_bus->probe_active == 0)
		wake_up(&nvdimm_bus->probe_wait);
	nvdimm_bus_unlock(&nvdimm_bus->dev);
}
