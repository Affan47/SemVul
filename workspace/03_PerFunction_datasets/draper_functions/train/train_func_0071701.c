ata_pci_device_resume(struct pci_dev *pdev)
{
	struct ata_host *host = pci_get_drvdata(pdev);
	int rc;

	rc = ata_pci_device_do_resume(pdev);
	if (rc == 0)
		ata_host_resume(host);
	return rc;
}
