ahd_linux_pci_dev_resume(struct pci_dev *pdev)
{
	struct ahd_softc *ahd = pci_get_drvdata(pdev);
	int rc;

	pci_set_power_state(pdev, PCI_D0);
	pci_restore_state(pdev);

	if ((rc = pci_enable_device(pdev))) {
		dev_printk(KERN_ERR, &pdev->dev,
			   "failed to enable device after resume (%d)\n", rc);
		return rc;
	}

	pci_set_master(pdev);

	ahd_pci_resume(ahd);

	ahd_resume(ahd);

	return rc;
}
