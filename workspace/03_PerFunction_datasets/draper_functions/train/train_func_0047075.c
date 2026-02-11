mvumi_probe_one(struct pci_dev *pdev, const struct pci_device_id *id)
{
	struct Scsi_Host *host;
	struct mvumi_hba *mhba;
	int ret;

	dev_dbg(&pdev->dev, " %#4.04x:%#4.04x:%#4.04x:%#4.04x: ",
			pdev->vendor, pdev->device, pdev->subsystem_vendor,
			pdev->subsystem_device);

	ret = pci_enable_device(pdev);
	if (ret)
		return ret;

	pci_set_master(pdev);

	if (IS_DMA64) {
		ret = pci_set_dma_mask(pdev, DMA_BIT_MASK(64));
		if (ret) {
			ret = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
			if (ret)
				goto fail_set_dma_mask;
		}
	} else {
		ret = pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
		if (ret)
			goto fail_set_dma_mask;
	}

	host = scsi_host_alloc(&mvumi_template, sizeof(*mhba));
	if (!host) {
		dev_err(&pdev->dev, "scsi_host_alloc failed\n");
		ret = -ENOMEM;
		goto fail_alloc_instance;
	}
	mhba = shost_priv(host);

	INIT_LIST_HEAD(&mhba->cmd_pool);
	INIT_LIST_HEAD(&mhba->ob_data_list);
	INIT_LIST_HEAD(&mhba->free_ob_list);
	INIT_LIST_HEAD(&mhba->res_list);
	INIT_LIST_HEAD(&mhba->waiting_req_list);
	mutex_init(&mhba->device_lock);
	INIT_LIST_HEAD(&mhba->mhba_dev_list);
	INIT_LIST_HEAD(&mhba->shost_dev_list);
	atomic_set(&mhba->fw_outstanding, 0);
	init_waitqueue_head(&mhba->int_cmd_wait_q);
	mutex_init(&mhba->sas_discovery_mutex);

	mhba->pdev = pdev;
	mhba->shost = host;
	mhba->unique_id = pdev->bus->number << 8 | pdev->devfn;

	ret = mvumi_init_fw(mhba);
	if (ret)
		goto fail_init_fw;

	ret = request_irq(mhba->pdev->irq, mvumi_isr_handler, IRQF_SHARED,
				"mvumi", mhba);
	if (ret) {
		dev_err(&pdev->dev, "failed to register IRQ\n");
		goto fail_init_irq;
	}

	mhba->instancet->enable_intr(mhba);
	pci_set_drvdata(pdev, mhba);

	ret = mvumi_io_attach(mhba);
	if (ret)
		goto fail_io_attach;

	mvumi_backup_bar_addr(mhba);
	dev_dbg(&pdev->dev, "probe mvumi driver successfully.\n");

	return 0;

fail_io_attach:
	mhba->instancet->disable_intr(mhba);
	free_irq(mhba->pdev->irq, mhba);
fail_init_irq:
	mvumi_release_fw(mhba);
fail_init_fw:
	scsi_host_put(host);

fail_alloc_instance:
fail_set_dma_mask:
	pci_disable_device(pdev);

	return ret;
}
