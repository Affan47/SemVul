netxen_mask_aer_correctable(struct netxen_adapter *adapter)
{
	struct pci_dev *pdev = adapter->pdev;
	struct pci_dev *root = pdev->bus->self;
	u32 aer_pos;


	if (!root)
		return;

	if (adapter->ahw.board_type != NETXEN_BRDTYPE_P3_4_GB_MM &&
		adapter->ahw.board_type != NETXEN_BRDTYPE_P3_10G_TP)
		return;

	if (pci_pcie_type(root) != PCI_EXP_TYPE_ROOT_PORT)
		return;

	aer_pos = pci_find_ext_capability(root, PCI_EXT_CAP_ID_ERR);
	if (!aer_pos)
		return;

	pci_write_config_dword(root, aer_pos + PCI_ERR_COR_MASK, 0xffff);
}
