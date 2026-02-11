ioat_dca_dev_managed(struct dca_provider *dca,
				struct device *dev)
{
	struct ioat_dca_priv *ioatdca = dca_priv(dca);
	struct pci_dev *pdev;
	int i;

	pdev = to_pci_dev(dev);
	for (i = 0; i < ioatdca->max_requesters; i++) {
		if (ioatdca->req_slots[i].pdev == pdev)
			return 1;
	}
	return 0;
}
