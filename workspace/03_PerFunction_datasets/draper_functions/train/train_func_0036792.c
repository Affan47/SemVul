nsc_ircc_pnp_probe(struct pnp_dev *dev, const struct pnp_device_id *id)
{
	memset(&pnp_info, 0, sizeof(chipio_t));
	pnp_info.irq = -1;
	pnp_info.dma = -1;
	pnp_succeeded = 1;

	if (id->driver_data & NSC_FORCE_DONGLE_TYPE9)
		dongle_id = 0x9;


	if (pnp_port_valid(dev, 0) &&
		!(pnp_port_flags(dev, 0) & IORESOURCE_DISABLED))
		pnp_info.fir_base = pnp_port_start(dev, 0);

	if (pnp_irq_valid(dev, 0) &&
		!(pnp_irq_flags(dev, 0) & IORESOURCE_DISABLED))
		pnp_info.irq = pnp_irq(dev, 0);

	if (pnp_dma_valid(dev, 0) &&
		!(pnp_dma_flags(dev, 0) & IORESOURCE_DISABLED))
		pnp_info.dma = pnp_dma(dev, 0);

	pr_debug("%s() : From PnP, found firbase 0x%03X ; irq %d ; dma %d.\n",
		 __func__, pnp_info.fir_base, pnp_info.irq, pnp_info.dma);

	if((pnp_info.fir_base == 0) ||
	   (pnp_info.irq == -1) || (pnp_info.dma == -1)) {


		pnp_succeeded = 0;
	}

	return 0;
}
