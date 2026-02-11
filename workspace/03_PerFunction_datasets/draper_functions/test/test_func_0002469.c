be_drv_init(struct be_adapter *adapter)
{
	struct be_dma_mem *mbox_mem_alloc = &adapter->mbox_mem_alloced;
	struct be_dma_mem *mbox_mem_align = &adapter->mbox_mem;
	struct be_dma_mem *rx_filter = &adapter->rx_filter;
	struct be_dma_mem *stats_cmd = &adapter->stats_cmd;
	struct device *dev = &adapter->pdev->dev;
	int status = 0;

	mbox_mem_alloc->size = sizeof(struct be_mcc_mailbox) + 16;
	mbox_mem_alloc->va = dma_zalloc_coherent(dev, mbox_mem_alloc->size,
						 &mbox_mem_alloc->dma,
						 GFP_KERNEL);
	if (!mbox_mem_alloc->va)
		return -ENOMEM;

	mbox_mem_align->size = sizeof(struct be_mcc_mailbox);
	mbox_mem_align->va = PTR_ALIGN(mbox_mem_alloc->va, 16);
	mbox_mem_align->dma = PTR_ALIGN(mbox_mem_alloc->dma, 16);

	rx_filter->size = sizeof(struct be_cmd_req_rx_filter);
	rx_filter->va = dma_zalloc_coherent(dev, rx_filter->size,
					    &rx_filter->dma, GFP_KERNEL);
	if (!rx_filter->va) {
		status = -ENOMEM;
		goto free_mbox;
	}

	if (lancer_chip(adapter))
		stats_cmd->size = sizeof(struct lancer_cmd_req_pport_stats);
	else if (BE2_chip(adapter))
		stats_cmd->size = sizeof(struct be_cmd_req_get_stats_v0);
	else if (BE3_chip(adapter))
		stats_cmd->size = sizeof(struct be_cmd_req_get_stats_v1);
	else
		stats_cmd->size = sizeof(struct be_cmd_req_get_stats_v2);
	stats_cmd->va = dma_zalloc_coherent(dev, stats_cmd->size,
					    &stats_cmd->dma, GFP_KERNEL);
	if (!stats_cmd->va) {
		status = -ENOMEM;
		goto free_rx_filter;
	}

	mutex_init(&adapter->mbox_lock);
	spin_lock_init(&adapter->mcc_lock);
	spin_lock_init(&adapter->mcc_cq_lock);
	init_completion(&adapter->et_cmd_compl);

	pci_save_state(adapter->pdev);

	INIT_DELAYED_WORK(&adapter->work, be_worker);
	INIT_DELAYED_WORK(&adapter->be_err_detection_work,
			  be_err_detection_task);

	adapter->rx_fc = true;
	adapter->tx_fc = true;


	adapter->be_get_temp_freq = 64;

	return 0;

free_rx_filter:
	dma_free_coherent(dev, rx_filter->size, rx_filter->va, rx_filter->dma);
free_mbox:
	dma_free_coherent(dev, mbox_mem_alloc->size, mbox_mem_alloc->va,
			  mbox_mem_alloc->dma);
	return status;
}
