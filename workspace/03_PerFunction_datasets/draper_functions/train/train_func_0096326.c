acpi_pci_slot_remove(struct pci_bus *bus)
{
	struct acpi_pci_slot *slot, *tmp;

	mutex_lock(&slot_list_lock);
	list_for_each_entry_safe(slot, tmp, &slot_list, list) {
		if (slot->pci_slot->bus == bus) {
			list_del(&slot->list);
			pci_destroy_slot(slot->pci_slot);
			put_device(&bus->dev);
			kfree(slot);
		}
	}
	mutex_unlock(&slot_list_lock);
}
