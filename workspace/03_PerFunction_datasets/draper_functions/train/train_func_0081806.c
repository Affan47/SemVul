rt2800usb_enable_radio(struct rt2x00_dev *rt2x00dev)
{
	u32 reg;

	if (unlikely(rt2800_wait_wpdma_ready(rt2x00dev)))
		return -EIO;

	rt2x00usb_register_read(rt2x00dev, USB_DMA_CFG, &reg);
	rt2x00_set_field32(&reg, USB_DMA_CFG_PHY_CLEAR, 0);
	rt2x00_set_field32(&reg, USB_DMA_CFG_RX_BULK_AGG_EN, 0);
	rt2x00_set_field32(&reg, USB_DMA_CFG_RX_BULK_AGG_TIMEOUT, 128);


	rt2x00_set_field32(&reg, USB_DMA_CFG_RX_BULK_AGG_LIMIT,
			   ((rt2x00dev->rx->limit * DATA_FRAME_SIZE)
			    / 1024) - 3);
	rt2x00_set_field32(&reg, USB_DMA_CFG_RX_BULK_EN, 1);
	rt2x00_set_field32(&reg, USB_DMA_CFG_TX_BULK_EN, 1);
	rt2x00usb_register_write(rt2x00dev, USB_DMA_CFG, reg);

	return rt2800_enable_radio(rt2x00dev);
}
