net2272_usb_reset(struct net2272 *dev)
{
	dev->gadget.speed = USB_SPEED_UNKNOWN;

	net2272_cancel_dma(dev);

	net2272_write(dev, IRQENB0, 0);
	net2272_write(dev, IRQENB1, 0);


	net2272_write(dev, IRQSTAT0, 0xff);
	net2272_write(dev, IRQSTAT1, ~(1 << SUSPEND_REQUEST_INTERRUPT));

	net2272_write(dev, DMAREQ,
		(0 << DMA_BUFFER_VALID) |
		(0 << DMA_REQUEST_ENABLE) |
		(1 << DMA_CONTROL_DACK) |
		(dev->dma_eot_polarity << EOT_POLARITY) |
		(dev->dma_dack_polarity << DACK_POLARITY) |
		(dev->dma_dreq_polarity << DREQ_POLARITY) |
		((dma_ep >> 1) << DMA_ENDPOINT_SELECT));

	net2272_cancel_dma(dev);
	net2272_set_fifo_mode(dev, (fifo_mode <= 3) ? fifo_mode : 0);


	net2272_write(dev, LOCCTL, net2272_read(dev, LOCCTL) | (1 << DATA_WIDTH));
	net2272_write(dev, LOCCTL1, (dma_mode << DMA_MODE));
}
