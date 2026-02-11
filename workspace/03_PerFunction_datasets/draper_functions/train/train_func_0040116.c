hptiop_unmap_pci_bar_itl(struct hptiop_hba *hba)
{
	if (hba->u.itl.plx)
		iounmap(hba->u.itl.plx);
	iounmap(hba->u.itl.iop);
}
