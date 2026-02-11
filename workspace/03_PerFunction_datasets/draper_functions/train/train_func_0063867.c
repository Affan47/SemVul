pcistub_device_id_remove(int domain, int bus, int slot, int func)
{
	struct pcistub_device_id *pci_dev_id, *t;
	int err = -ENOENT;
	unsigned long flags;

	spin_lock_irqsave(&device_ids_lock, flags);
	list_for_each_entry_safe(pci_dev_id, t, &pcistub_device_ids,
				 slot_list) {
		if (pci_dev_id->domain == domain && pci_dev_id->bus == bus
		    && (slot < 0 || PCI_SLOT(pci_dev_id->devfn) == slot)
		    && (func < 0 || PCI_FUNC(pci_dev_id->devfn) == func)) {


			list_del(&pci_dev_id->slot_list);
			kfree(pci_dev_id);

			err = 0;

			pr_debug("removed %04x:%02x:%02x.%d from seize list\n",
				 domain, bus, slot, func);
		}
	}
	spin_unlock_irqrestore(&device_ids_lock, flags);

	return err;
}
