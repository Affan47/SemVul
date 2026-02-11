eeepc_get_adapter_status(struct hotplug_slot *hotplug_slot,
				    u8 *value)
{
	struct eeepc_laptop *eeepc = hotplug_slot->private;
	int val = get_acpi(eeepc, CM_ASL_WLAN);

	if (val == 1 || val == 0)
		*value = val;
	else
		return -EINVAL;

	return 0;
}
