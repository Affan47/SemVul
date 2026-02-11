beiscsi_remove(struct pci_dev *pcidev)
{

	struct beiscsi_hba *phba = NULL;

	phba = pci_get_drvdata(pcidev);
	if (!phba) {
		dev_err(&pcidev->dev, "beiscsi_remove called with no phba\n");
		return;
	}

	beiscsi_destroy_def_ifaces(phba);
	beiscsi_quiesce(phba, BEISCSI_CLEAN_UNLOAD);
	iscsi_boot_destroy_kset(phba->boot_kset);
	iscsi_host_remove(phba->shost);
	pci_dev_put(phba->pcidev);
	iscsi_host_free(phba->shost);
	pci_disable_pcie_error_reporting(pcidev);
	pci_set_drvdata(pcidev, NULL);
	pci_release_regions(pcidev);
	pci_disable_device(pcidev);
}
