piix_pci_device_resume(struct pci_dev *pdev)
{
	struct ata_host *host = pci_get_drvdata(pdev);
	unsigned long flags;
	int rc;

	if (host->flags & PIIX_HOST_BROKEN_SUSPEND) {
		spin_lock_irqsave(&host->lock, flags);
		host->flags &= ~PIIX_HOST_BROKEN_SUSPEND;
		spin_unlock_irqrestore(&host->lock, flags);

		pci_set_power_state(pdev, PCI_D0);
		pci_restore_state(pdev);


		rc = pci_reenable_device(pdev);
		if (rc)
			dev_err(&pdev->dev,
				"failed to enable device after resume (%d)\n",
				rc);
	} else
		rc = ata_pci_device_do_resume(pdev);

	if (rc == 0)
		ata_host_resume(host);

	return rc;
}
