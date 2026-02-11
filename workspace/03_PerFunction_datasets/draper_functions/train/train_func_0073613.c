pci_enable_msix(struct pci_dev *dev, struct msix_entry *entries, int nvec)
{
	int nr_entries;
	int i, j;

	if (!pci_msi_supported(dev, nvec))
		return -EINVAL;

	if (!entries)
		return -EINVAL;

	nr_entries = pci_msix_vec_count(dev);
	if (nr_entries < 0)
		return nr_entries;
	if (nvec > nr_entries)
		return nr_entries;


	for (i = 0; i < nvec; i++) {
		if (entries[i].entry >= nr_entries)
			return -EINVAL;
		for (j = i + 1; j < nvec; j++) {
			if (entries[i].entry == entries[j].entry)
				return -EINVAL;
		}
	}
	WARN_ON(!!dev->msix_enabled);


	if (dev->msi_enabled) {
		dev_info(&dev->dev, "can't enable MSI-X (MSI IRQ already assigned)\n");
		return -EINVAL;
	}
	return msix_capability_init(dev, entries, nvec);
}
