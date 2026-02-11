x38_remove_one(struct pci_dev *pdev)
{
	struct mem_ctl_info *mci;

	edac_dbg(0, "\n");

	mci = edac_mc_del_mc(&pdev->dev);
	if (!mci)
		return;

	iounmap(mci->pvt_info);

	edac_mc_free(mci);
}
