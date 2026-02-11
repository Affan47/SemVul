acpi_power_wakeup_list_init(struct list_head *list, int *system_level_p)
{
	struct acpi_power_resource_entry *entry;
	int system_level = 5;

	list_for_each_entry(entry, list, node) {
		struct acpi_power_resource *resource = entry->resource;
		acpi_handle handle = resource->device.handle;
		int result;
		int state;

		mutex_lock(&resource->resource_lock);

		result = acpi_power_get_state(handle, &state);
		if (result) {
			mutex_unlock(&resource->resource_lock);
			return result;
		}
		if (state == ACPI_POWER_RESOURCE_STATE_ON) {
			resource->ref_count++;
			resource->wakeup_enabled = true;
		}
		if (system_level > resource->system_level)
			system_level = resource->system_level;

		mutex_unlock(&resource->resource_lock);
	}
	*system_level_p = system_level;
	return 0;
}
