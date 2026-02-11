quirk_amd_nb_node(struct pci_dev *dev)
{
	struct pci_dev *nb_ht;
	unsigned int devfn;
	u32 node;
	u32 val;

	devfn = PCI_DEVFN(PCI_SLOT(dev->devfn), 0);
	nb_ht = pci_get_slot(dev->bus, devfn);
	if (!nb_ht)
		return;

	pci_read_config_dword(nb_ht, 0x60, &val);
	node = pcibus_to_node(dev->bus) | (val & 7);


	if (node_online(node))
		set_dev_node(&dev->dev, node);
	pci_dev_put(nb_ht);
}
