netup_unidvb_dma_timeout(unsigned long data)
{
	struct netup_dma *dma = (struct netup_dma *)data;
	struct netup_unidvb_dev *ndev = dma->ndev;

	dev_dbg(&ndev->pci_dev->dev, "%s()\n", __func__);
	netup_unidvb_queue_cleanup(dma);
}
