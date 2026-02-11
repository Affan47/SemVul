hpsa_remove_one(struct pci_dev *pdev)
{
	struct ctlr_info *h;
	unsigned long flags;

	if (pci_get_drvdata(pdev) == NULL) {
		dev_err(&pdev->dev, "unable to remove device\n");
		return;
	}
	h = pci_get_drvdata(pdev);


	spin_lock_irqsave(&h->lock, flags);
	h->remove_in_progress = 1;
	spin_unlock_irqrestore(&h->lock, flags);
	cancel_delayed_work_sync(&h->monitor_ctlr_work);
	cancel_delayed_work_sync(&h->rescan_ctlr_work);
	destroy_workqueue(h->rescan_ctlr_wq);
	destroy_workqueue(h->resubmit_wq);

	hpsa_delete_sas_host(h);


	if (h->scsi_host)
		scsi_remove_host(h->scsi_host);


	hpsa_shutdown(pdev);

	hpsa_free_device_info(h);

	kfree(h->hba_inquiry_data);
	h->hba_inquiry_data = NULL;
	hpsa_free_ioaccel2_sg_chain_blocks(h);
	hpsa_free_performant_mode(h);
	hpsa_free_sg_chain_blocks(h);
	hpsa_free_cmd_pool(h);
	kfree(h->lastlogicals);


	scsi_host_put(h->scsi_host);
	h->scsi_host = NULL;


	hpsa_free_pci_init(h);

	free_percpu(h->lockup_detected);
	h->lockup_detected = NULL;


	kfree(h);
}
