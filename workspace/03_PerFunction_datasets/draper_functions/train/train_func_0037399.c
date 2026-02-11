__acpi_pci_root_release_info(struct acpi_pci_root_info *info)
{
	struct resource *res;
	struct resource_entry *entry, *tmp;

	if (!info)
		return;

	resource_list_for_each_entry_safe(entry, tmp, &info->resources) {
		res = entry->res;
		if (res->parent &&
		    (res->flags & (IORESOURCE_MEM | IORESOURCE_IO)))
			release_resource(res);
		resource_list_destroy_entry(entry);
	}

	info->ops->release_info(info);
}
