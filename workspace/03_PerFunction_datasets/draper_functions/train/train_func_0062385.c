__pciehp_link_set(struct controller *ctrl, bool enable)
{
	struct pci_dev *pdev = ctrl_dev(ctrl);
	u16 lnk_ctrl;

	pcie_capability_read_word(pdev, PCI_EXP_LNKCTL, &lnk_ctrl);

	if (enable)
		lnk_ctrl &= ~PCI_EXP_LNKCTL_LD;
	else
		lnk_ctrl |= PCI_EXP_LNKCTL_LD;

	pcie_capability_write_word(pdev, PCI_EXP_LNKCTL, lnk_ctrl);
	ctrl_dbg(ctrl, "%s: lnk_ctrl = %x\n", __func__, lnk_ctrl);
	return 0;
}
