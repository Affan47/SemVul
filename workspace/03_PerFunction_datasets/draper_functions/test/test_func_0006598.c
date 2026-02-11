nic_remove(struct pci_dev *pdev)
{
	struct nicpf *nic = pci_get_drvdata(pdev);

	if (nic->flags & NIC_SRIOV_ENABLED)
		pci_disable_sriov(pdev);

	if (nic->check_link) {

		cancel_delayed_work_sync(&nic->dwork);
		destroy_workqueue(nic->check_link);
	}

	nic_unregister_interrupts(nic);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	pci_set_drvdata(pdev, NULL);
}
