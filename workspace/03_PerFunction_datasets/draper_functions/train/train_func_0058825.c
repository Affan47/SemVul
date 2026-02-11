init_pci_cap_vpd_perm(struct perm_bits *perm)
{
	if (alloc_perm_bits(perm, pci_cap_length[PCI_CAP_ID_VPD]))
		return -ENOMEM;

	perm->writefn = vfio_vpd_config_write;


	p_setb(perm, PCI_CAP_LIST_NEXT, (u8)ALL_VIRT, NO_WRITE);


	p_setw(perm, PCI_VPD_ADDR, (u16)ALL_VIRT, (u16)ALL_WRITE);
	p_setd(perm, PCI_VPD_DATA, ALL_VIRT, ALL_WRITE);

	return 0;
}
