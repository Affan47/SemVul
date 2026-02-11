typhoon_interrupt(int irq, void *dev_instance)
{
	struct net_device *dev = dev_instance;
	struct typhoon *tp = netdev_priv(dev);
	void __iomem *ioaddr = tp->ioaddr;
	u32 intr_status;

	intr_status = ioread32(ioaddr + TYPHOON_REG_INTR_STATUS);
	if(!(intr_status & TYPHOON_INTR_HOST_INT))
		return IRQ_NONE;

	iowrite32(intr_status, ioaddr + TYPHOON_REG_INTR_STATUS);

	if (napi_schedule_prep(&tp->napi)) {
		iowrite32(TYPHOON_INTR_ALL, ioaddr + TYPHOON_REG_INTR_MASK);
		typhoon_post_pci_writes(ioaddr);
		__napi_schedule(&tp->napi);
	} else {
		netdev_err(dev, "Error, poll already scheduled\n");
	}
	return IRQ_HANDLED;
}
