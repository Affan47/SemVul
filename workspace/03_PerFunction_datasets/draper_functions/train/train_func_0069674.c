pcistub_quirk_show(struct device_driver *drv, char *buf)
{
	int count = 0;
	unsigned long flags;
	struct xen_pcibk_config_quirk *quirk;
	struct xen_pcibk_dev_data *dev_data;
	const struct config_field *field;
	const struct config_field_entry *cfg_entry;

	spin_lock_irqsave(&device_ids_lock, flags);
	list_for_each_entry(quirk, &xen_pcibk_quirks, quirks_list) {
		if (count >= PAGE_SIZE)
			goto out;

		count += scnprintf(buf + count, PAGE_SIZE - count,
				   "%02x:%02x.%01x\n\t%04x:%04x:%04x:%04x\n",
				   quirk->pdev->bus->number,
				   PCI_SLOT(quirk->pdev->devfn),
				   PCI_FUNC(quirk->pdev->devfn),
				   quirk->devid.vendor, quirk->devid.device,
				   quirk->devid.subvendor,
				   quirk->devid.subdevice);

		dev_data = pci_get_drvdata(quirk->pdev);

		list_for_each_entry(cfg_entry, &dev_data->config_fields, list) {
			field = cfg_entry->field;
			if (count >= PAGE_SIZE)
				goto out;

			count += scnprintf(buf + count, PAGE_SIZE - count,
					   "\t\t%08x:%01x:%08x\n",
					   cfg_entry->base_offset +
					   field->offset, field->size,
					   field->mask);
		}
	}

out:
	spin_unlock_irqrestore(&device_ids_lock, flags);

	return count;
}
