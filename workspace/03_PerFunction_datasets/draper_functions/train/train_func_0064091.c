has_power_file(struct pci_slot *pci_slot)
{
	struct hotplug_slot *slot = pci_slot->hotplug;

	if ((!slot) || (!slot->ops))
		return false;
	if ((slot->ops->enable_slot) ||
	    (slot->ops->disable_slot) ||
	    (slot->ops->get_power_status))
		return true;
	return false;
}
