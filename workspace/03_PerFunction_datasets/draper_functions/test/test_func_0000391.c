cxgb_enable_msix(struct adapter *adap)
{
	struct msix_entry entries[SGE_QSETS + 1];
	int vectors;
	int i;

	vectors = ARRAY_SIZE(entries);
	for (i = 0; i < vectors; ++i)
		entries[i].entry = i;

	vectors = pci_enable_msix_range(adap->pdev, entries,
					adap->params.nports + 1, vectors);
	if (vectors < 0)
		return vectors;

	for (i = 0; i < vectors; ++i)
		adap->msix_info[i].vec = entries[i].vector;
	adap->msix_nvectors = vectors;

	return 0;
}
