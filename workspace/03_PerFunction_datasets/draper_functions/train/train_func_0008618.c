lpfc_dual_chute_pci_bar_map(struct lpfc_hba *phba, uint16_t pci_barset)
{
	if (!phba->pcidev)
		return NULL;

	switch (pci_barset) {
	case WQ_PCI_BAR_0_AND_1:
		return phba->pci_bar0_memmap_p;
	case WQ_PCI_BAR_2_AND_3:
		return phba->pci_bar2_memmap_p;
	case WQ_PCI_BAR_4_AND_5:
		return phba->pci_bar4_memmap_p;
	default:
		break;
	}
	return NULL;
}
