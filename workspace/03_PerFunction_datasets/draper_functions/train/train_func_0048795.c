wbsd_pnp_probe(struct pnp_dev *pnpdev, const struct pnp_device_id *dev_id)
{
	int io, irq, dma;


	io = pnp_port_start(pnpdev, 0);
	irq = pnp_irq(pnpdev, 0);
	if (pnp_dma_valid(pnpdev, 0))
		dma = pnp_dma(pnpdev, 0);
	else
		dma = -1;

	DBGF("PnP resources: port %3x irq %d dma %d\n", io, irq, dma);

	return wbsd_init(&pnpdev->dev, io, irq, dma, 1);
}
