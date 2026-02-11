pci_vc_enable(struct pci_dev *dev, int pos, int res)
{
	int ctrl_pos, status_pos, id, pos2, evcc, i, ctrl_pos2, status_pos2;
	u32 ctrl, header, cap1, ctrl2;
	struct pci_dev *link = NULL;


	if (!dev->has_secondary_link)
		return;

	ctrl_pos = pos + PCI_VC_RES_CTRL + (res * PCI_CAP_VC_PER_VC_SIZEOF);
	status_pos = pos + PCI_VC_RES_STATUS + (res * PCI_CAP_VC_PER_VC_SIZEOF);

	pci_read_config_dword(dev, ctrl_pos, &ctrl);
	id = ctrl & PCI_VC_RES_CTRL_ID;

	pci_read_config_dword(dev, pos, &header);


	if (PCI_EXT_CAP_ID(header) == PCI_EXT_CAP_ID_VC9 ||
	    pci_is_root_bus(dev->bus))
		goto enable;

	pos2 = pci_find_ext_capability(dev->bus->self, PCI_EXT_CAP_ID_VC);
	if (!pos2)
		goto enable;

	pci_read_config_dword(dev->bus->self, pos2 + PCI_VC_PORT_CAP1, &cap1);
	evcc = cap1 & PCI_VC_CAP1_EVCC;


	for (i = 1; i < evcc + 1; i++) {
		ctrl_pos2 = pos2 + PCI_VC_RES_CTRL +
				(i * PCI_CAP_VC_PER_VC_SIZEOF);
		status_pos2 = pos2 + PCI_VC_RES_STATUS +
				(i * PCI_CAP_VC_PER_VC_SIZEOF);
		pci_read_config_dword(dev->bus->self, ctrl_pos2, &ctrl2);
		if ((ctrl2 & PCI_VC_RES_CTRL_ID) == id) {
			link = dev->bus->self;
			break;
		}
	}

	if (!link)
		goto enable;


	if (ctrl2 & PCI_VC_RES_CTRL_ENABLE) {
		ctrl2 &= ~PCI_VC_RES_CTRL_ENABLE;
		pci_write_config_dword(link, ctrl_pos2, ctrl2);
	}


	ctrl2 |= PCI_VC_RES_CTRL_ENABLE;
	pci_write_config_dword(link, ctrl_pos2, ctrl2);
enable:
	ctrl |= PCI_VC_RES_CTRL_ENABLE;
	pci_write_config_dword(dev, ctrl_pos, ctrl);

	if (!pci_wait_for_pending(dev, status_pos, PCI_VC_RES_STATUS_NEGO))
		dev_err(&dev->dev, "VC%d negotiation stuck pending\n", id);

	if (link && !pci_wait_for_pending(link, status_pos2,
					  PCI_VC_RES_STATUS_NEGO))
		dev_err(&link->dev, "VC%d negotiation stuck pending\n", id);
}
