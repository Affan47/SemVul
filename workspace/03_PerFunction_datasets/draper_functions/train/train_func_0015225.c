vmxnet3_remove_device(struct pci_dev *pdev)
{
	struct net_device *netdev = pci_get_drvdata(pdev);
	struct vmxnet3_adapter *adapter = netdev_priv(netdev);
	int size = 0;
	int num_rx_queues;

#ifdef VMXNET3_RSS
	if (enable_mq)
		num_rx_queues = min(VMXNET3_DEVICE_MAX_RX_QUEUES,
				    (int)num_online_cpus());
	else
#endif
		num_rx_queues = 1;
	num_rx_queues = rounddown_pow_of_two(num_rx_queues);

	cancel_work_sync(&adapter->work);

	unregister_netdev(netdev);

	vmxnet3_free_intr_resources(adapter);
	vmxnet3_free_pci_resources(adapter);
#ifdef VMXNET3_RSS
	dma_free_coherent(&adapter->pdev->dev, sizeof(struct UPT1_RSSConf),
			  adapter->rss_conf, adapter->rss_conf_pa);
#endif
	dma_free_coherent(&adapter->pdev->dev, sizeof(struct Vmxnet3_PMConf),
			  adapter->pm_conf, adapter->pm_conf_pa);

	size = sizeof(struct Vmxnet3_TxQueueDesc) * adapter->num_tx_queues;
	size += sizeof(struct Vmxnet3_RxQueueDesc) * num_rx_queues;
	dma_free_coherent(&adapter->pdev->dev, size, adapter->tqd_start,
			  adapter->queue_desc_pa);
	dma_free_coherent(&adapter->pdev->dev,
			  sizeof(struct Vmxnet3_DriverShared),
			  adapter->shared, adapter->shared_pa);
	dma_unmap_single(&adapter->pdev->dev, adapter->adapter_pa,
			 sizeof(struct vmxnet3_adapter), PCI_DMA_TODEVICE);
	free_netdev(netdev);
}
