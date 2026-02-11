i82975x_init_one(struct pci_dev *pdev,
			    const struct pci_device_id *ent)
{
	int rc;

	edac_dbg(0, "\n");

	if (pci_enable_device(pdev) < 0)
		return -EIO;

	rc = i82975x_probe1(pdev, ent->driver_data);

	if (mci_pdev == NULL)
		mci_pdev = pci_dev_get(pdev);

	return rc;
}
