megaraid_probe_one(struct pci_dev *pdev, const struct pci_device_id *id)
{
	adapter_t	*adapter;


	con_log(CL_ANN, (KERN_INFO
		"megaraid: probe new device %#4.04x:%#4.04x:%#4.04x:%#4.04x: ",
		pdev->vendor, pdev->device, pdev->subsystem_vendor,
		pdev->subsystem_device));

	con_log(CL_ANN, ("bus %d:slot %d:func %d\n", pdev->bus->number,
		PCI_SLOT(pdev->devfn), PCI_FUNC(pdev->devfn)));

	if (pci_enable_device(pdev)) {
		con_log(CL_ANN, (KERN_WARNING
				"megaraid: pci_enable_device failed\n"));

		return -ENODEV;
	}


	pci_set_master(pdev);


	adapter = kzalloc(sizeof(adapter_t), GFP_KERNEL);

	if (adapter == NULL) {
		con_log(CL_ANN, (KERN_WARNING
		"megaraid: out of memory, %s %d.\n", __func__, __LINE__));

		goto out_probe_one;
	}


	adapter->unique_id	= pdev->bus->number << 8 | pdev->devfn;
	adapter->irq		= pdev->irq;
	adapter->pdev		= pdev;

	atomic_set(&adapter->being_detached, 0);


	if (pci_set_dma_mask(adapter->pdev, DMA_BIT_MASK(32)) != 0) {

		con_log(CL_ANN, (KERN_WARNING
			"megaraid: pci_set_dma_mask failed:%d\n", __LINE__));

		goto out_free_adapter;
	}


	spin_lock_init(&adapter->lock);


	INIT_LIST_HEAD(&adapter->kscb_pool);
	spin_lock_init(SCSI_FREE_LIST_LOCK(adapter));

	INIT_LIST_HEAD(&adapter->pend_list);
	spin_lock_init(PENDING_LIST_LOCK(adapter));

	INIT_LIST_HEAD(&adapter->completed_list);
	spin_lock_init(COMPLETED_LIST_LOCK(adapter));


	if (megaraid_init_mbox(adapter) != 0) {
		con_log(CL_ANN, (KERN_WARNING
			"megaraid: maibox adapter did not initialize\n"));

		goto out_free_adapter;
	}


	if (megaraid_cmm_register(adapter) != 0) {

		con_log(CL_ANN, (KERN_WARNING
		"megaraid: could not register with management module\n"));

		goto out_fini_mbox;
	}


	pci_set_drvdata(pdev, adapter);


	if (megaraid_io_attach(adapter) != 0) {

		con_log(CL_ANN, (KERN_WARNING "megaraid: io attach failed\n"));

		goto out_cmm_unreg;
	}

	return 0;

out_cmm_unreg:
	megaraid_cmm_unregister(adapter);
out_fini_mbox:
	megaraid_fini_mbox(adapter);
out_free_adapter:
	kfree(adapter);
out_probe_one:
	pci_disable_device(pdev);

	return -ENODEV;
}
