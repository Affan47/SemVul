dbg_ctrl(struct controller *ctrl)
{
	struct pci_dev *pdev = ctrl->pcie->port;
	u16 reg16;

	if (!pciehp_debug)
		return;

	ctrl_info(ctrl, "Slot Capabilities      : 0x%08x\n", ctrl->slot_cap);
	pcie_capability_read_word(pdev, PCI_EXP_SLTSTA, &reg16);
	ctrl_info(ctrl, "Slot Status            : 0x%04x\n", reg16);
	pcie_capability_read_word(pdev, PCI_EXP_SLTCTL, &reg16);
	ctrl_info(ctrl, "Slot Control           : 0x%04x\n", reg16);
}
