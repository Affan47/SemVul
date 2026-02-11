quirk_intel_qat_vf_cap(struct pci_dev *pdev)
{
	int pos, i = 0;
	u8 next_cap;
	u16 reg16, *cap;
	struct pci_cap_saved_state *state;


	if (pdev->pcie_cap || pci_find_capability(pdev, PCI_CAP_ID_EXP))
		return;


	pos = pci_find_capability(pdev, PCI_CAP_ID_MSI);
	if (!pos)
		return;


	pci_read_config_byte(pdev, pos + 1, &next_cap);
	if (next_cap)
		return;


	pos = 0x50;
	pci_read_config_word(pdev, pos, &reg16);
	if (reg16 == (0x0000 | PCI_CAP_ID_EXP)) {
		u32 status;
#ifndef PCI_EXP_SAVE_REGS
#define PCI_EXP_SAVE_REGS     7
#endif
		int size = PCI_EXP_SAVE_REGS * sizeof(u16);

		pdev->pcie_cap = pos;
		pci_read_config_word(pdev, pos + PCI_EXP_FLAGS, &reg16);
		pdev->pcie_flags_reg = reg16;
		pci_read_config_word(pdev, pos + PCI_EXP_DEVCAP, &reg16);
		pdev->pcie_mpss = reg16 & PCI_EXP_DEVCAP_PAYLOAD;

		pdev->cfg_size = PCI_CFG_SPACE_EXP_SIZE;
		if (pci_read_config_dword(pdev, PCI_CFG_SPACE_SIZE, &status) !=
		    PCIBIOS_SUCCESSFUL || (status == 0xffffffff))
			pdev->cfg_size = PCI_CFG_SPACE_SIZE;

		if (pci_find_saved_cap(pdev, PCI_CAP_ID_EXP))
			return;


		state = kzalloc(sizeof(*state) + size, GFP_KERNEL);
		if (!state)
			return;

		state->cap.cap_nr = PCI_CAP_ID_EXP;
		state->cap.cap_extended = 0;
		state->cap.size = size;
		cap = (u16 *)&state->cap.data[0];
		pcie_capability_read_word(pdev, PCI_EXP_DEVCTL, &cap[i++]);
		pcie_capability_read_word(pdev, PCI_EXP_LNKCTL, &cap[i++]);
		pcie_capability_read_word(pdev, PCI_EXP_SLTCTL, &cap[i++]);
		pcie_capability_read_word(pdev, PCI_EXP_RTCTL,  &cap[i++]);
		pcie_capability_read_word(pdev, PCI_EXP_DEVCTL2, &cap[i++]);
		pcie_capability_read_word(pdev, PCI_EXP_LNKCTL2, &cap[i++]);
		pcie_capability_read_word(pdev, PCI_EXP_SLTCTL2, &cap[i++]);
		hlist_add_head(&state->next, &pdev->saved_cap_space);
	}
}
