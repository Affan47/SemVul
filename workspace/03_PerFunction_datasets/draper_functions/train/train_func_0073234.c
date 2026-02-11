amd_iommu_get_dm_regions(struct device *dev,
				     struct list_head *head)
{
	struct unity_map_entry *entry;
	u16 devid;

	devid = get_device_id(dev);

	list_for_each_entry(entry, &amd_iommu_unity_map, list) {
		struct iommu_dm_region *region;

		if (devid < entry->devid_start || devid > entry->devid_end)
			continue;

		region = kzalloc(sizeof(*region), GFP_KERNEL);
		if (!region) {
			pr_err("Out of memory allocating dm-regions for %s\n",
				dev_name(dev));
			return;
		}

		region->start = entry->address_start;
		region->length = entry->address_end - entry->address_start;
		if (entry->prot & IOMMU_PROT_IR)
			region->prot |= IOMMU_READ;
		if (entry->prot & IOMMU_PROT_IW)
			region->prot |= IOMMU_WRITE;

		list_add_tail(&region->list, head);
	}
}
