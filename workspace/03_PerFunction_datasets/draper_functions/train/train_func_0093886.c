bcma_core_pci_extend_L1timer(struct bcma_drv_pci *pc, bool extend)
{
	u32 w;

	w = bcma_pcie_read(pc, BCMA_CORE_PCI_DLLP_PMTHRESHREG);
	if (extend)
		w |= BCMA_CORE_PCI_ASPMTIMER_EXTEND;
	else
		w &= ~BCMA_CORE_PCI_ASPMTIMER_EXTEND;
	bcma_pcie_write(pc, BCMA_CORE_PCI_DLLP_PMTHRESHREG, w);
	bcma_pcie_read(pc, BCMA_CORE_PCI_DLLP_PMTHRESHREG);
}
