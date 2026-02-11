aac_rx_intr_producer(int irq, void *dev_id)
{
	struct aac_dev *dev = dev_id;
	unsigned long bellbits;
	u8 intstat = rx_readb(dev, MUnit.OISR);


	if (likely(intstat & ~(dev->OIMR))) {
		bellbits = rx_readl(dev, OutboundDoorbellReg);
		if (unlikely(bellbits & DoorBellPrintfReady)) {
			aac_printf(dev, readl (&dev->IndexRegs->Mailbox[5]));
			rx_writel(dev, MUnit.ODR,DoorBellPrintfReady);
			rx_writel(dev, InboundDoorbellReg,DoorBellPrintfDone);
		}
		else if (unlikely(bellbits & DoorBellAdapterNormCmdReady)) {
			rx_writel(dev, MUnit.ODR, DoorBellAdapterNormCmdReady);
			aac_command_normal(&dev->queues->queue[HostNormCmdQueue]);
		}
		else if (likely(bellbits & DoorBellAdapterNormRespReady)) {
			rx_writel(dev, MUnit.ODR,DoorBellAdapterNormRespReady);
			aac_response_normal(&dev->queues->queue[HostNormRespQueue]);
		}
		else if (unlikely(bellbits & DoorBellAdapterNormCmdNotFull)) {
			rx_writel(dev, MUnit.ODR, DoorBellAdapterNormCmdNotFull);
		}
		else if (unlikely(bellbits & DoorBellAdapterNormRespNotFull)) {
			rx_writel(dev, MUnit.ODR, DoorBellAdapterNormCmdNotFull);
			rx_writel(dev, MUnit.ODR, DoorBellAdapterNormRespNotFull);
		}
		return IRQ_HANDLED;
	}
	return IRQ_NONE;
}
