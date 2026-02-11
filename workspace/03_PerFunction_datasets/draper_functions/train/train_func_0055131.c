ie31200_remove_one(struct pci_dev *pdev)
{
	struct mem_ctl_info *mci;
	struct ie31200_priv *priv;

	edac_dbg(0, "\n");
	mci = edac_mc_del_mc(&pdev->dev);
	if (!mci)
		return;
	priv = mci->pvt_info;
	iounmap(priv->window);
	edac_mc_free(mci);
}
