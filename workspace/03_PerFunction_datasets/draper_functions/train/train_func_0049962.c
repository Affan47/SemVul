twa_remove(struct pci_dev *pdev)
{
	struct Scsi_Host *host = pci_get_drvdata(pdev);
	TW_Device_Extension *tw_dev = (TW_Device_Extension *)host->hostdata;

	scsi_remove_host(tw_dev->host);


	if (twa_major >= 0) {
		unregister_chrdev(twa_major, "twa");
		twa_major = -1;
	}


	__twa_shutdown(tw_dev);


	if (test_bit(TW_USING_MSI, &tw_dev->flags))
		pci_disable_msi(pdev);


	iounmap(tw_dev->base_addr);


	pci_release_regions(pdev);


	twa_free_device_extension(tw_dev);

	scsi_host_put(tw_dev->host);
	pci_disable_device(pdev);
	twa_device_extension_count--;
}
