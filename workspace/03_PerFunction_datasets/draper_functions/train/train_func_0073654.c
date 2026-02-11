rbtn_rfkill_query(struct rfkill *rfkill, void *data)
{
	struct acpi_device *device = data;
	int state;

	state = rbtn_get(device);
	if (state < 0)
		return;

	rfkill_set_states(rfkill, state, state);
}
