ehci_moschip_read_frame_index(struct ehci_hcd *ehci)
{
	unsigned uf;

	uf = ehci_readl(ehci, &ehci->regs->frame_index);
	if (unlikely((uf & 7) == 0))
		uf = ehci_readl(ehci, &ehci->regs->frame_index);
	return uf;
}
