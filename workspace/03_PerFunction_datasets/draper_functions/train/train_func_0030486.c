pci_msi_shutdown(struct pci_dev *dev)
{
	struct msi_desc *desc;
	u32 mask;

	if (!pci_msi_enable || !dev || !dev->msi_enabled)
		return;

	BUG_ON(list_empty(dev_to_msi_list(&dev->dev)));
	desc = first_pci_msi_entry(dev);

	pci_msi_set_enable(dev, 0);
	pci_intx_for_msi(dev, 1);
	dev->msi_enabled = 0;


	mask = msi_mask(desc->msi_attrib.multi_cap);

	__pci_msi_desc_mask_irq(desc, mask, ~mask);


	dev->irq = desc->msi_attrib.default_irq;
	pcibios_alloc_irq(dev);
}
