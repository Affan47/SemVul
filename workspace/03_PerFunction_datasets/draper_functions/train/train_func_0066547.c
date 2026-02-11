acpi_power_resources_list_add(acpi_handle handle,
					 struct list_head *list)
{
	struct acpi_power_resource *resource = acpi_power_get_context(handle);
	struct acpi_power_resource_entry *entry;

	if (!resource || !list)
		return -EINVAL;

	entry = kzalloc(sizeof(*entry), GFP_KERNEL);
	if (!entry)
		return -ENOMEM;

	entry->resource = resource;
	if (!list_empty(list)) {
		struct acpi_power_resource_entry *e;

		list_for_each_entry(e, list, node)
			if (e->resource->order > resource->order) {
				list_add_tail(&entry->node, &e->node);
				return 0;
			}
	}
	list_add_tail(&entry->node, list);
	return 0;
}
