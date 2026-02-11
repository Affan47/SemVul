add_memdev(struct acpi_nfit_desc *acpi_desc,
		struct nfit_table_prev *prev,
		struct acpi_nfit_memory_map *memdev)
{
	size_t length = min_t(size_t, sizeof(*memdev), memdev->header.length);
	struct device *dev = acpi_desc->dev;
	struct nfit_memdev *nfit_memdev;

	list_for_each_entry(nfit_memdev, &prev->memdevs, list)
		if (memcmp(nfit_memdev->memdev, memdev, length) == 0) {
			list_move_tail(&nfit_memdev->list, &acpi_desc->memdevs);
			return true;
		}

	nfit_memdev = devm_kzalloc(dev, sizeof(*nfit_memdev), GFP_KERNEL);
	if (!nfit_memdev)
		return false;
	INIT_LIST_HEAD(&nfit_memdev->list);
	nfit_memdev->memdev = memdev;
	list_add_tail(&nfit_memdev->list, &acpi_desc->memdevs);
	dev_dbg(dev, "%s: memdev handle: %#x spa: %d dcr: %d\n",
			__func__, memdev->device_handle, memdev->range_index,
			memdev->region_index);
	return true;
}
