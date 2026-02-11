net2272_start_dma(struct net2272 *dev)
{

#ifdef CONFIG_PCI
	switch (dev->dev_id) {
	case PCI_DEVICE_ID_RDK1:
		writeb((1 << CHANNEL_ENABLE) | (1 << CHANNEL_START),
			dev->rdk1.plx9054_base_addr + DMACSR0);
		break;
	}
#endif
}
