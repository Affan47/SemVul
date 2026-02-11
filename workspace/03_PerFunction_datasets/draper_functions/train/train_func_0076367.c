prism2_pci_cor_sreset(local_info_t *local)
{
	struct net_device *dev = local->dev;
	u16 reg;

	reg = HFA384X_INB(HFA384X_PCICOR_OFF);
	printk(KERN_DEBUG "%s: Original COR value: 0x%0x\n", dev->name, reg);


#ifdef PRISM2_PCI_USE_LONG_DELAYS
	int i;

	HFA384X_OUTW(reg | 0x0080, HFA384X_PCICOR_OFF);
	mdelay(250);

	HFA384X_OUTW(reg & ~0x0080, HFA384X_PCICOR_OFF);
	mdelay(500);


	i = 2000000 / 10;
	while ((HFA384X_INW(HFA384X_CMD_OFF) & HFA384X_CMD_BUSY) && --i)
		udelay(10);

#else

	HFA384X_OUTW(reg | 0x0080, HFA384X_PCICOR_OFF);
	mdelay(2);
	HFA384X_OUTW(reg & ~0x0080, HFA384X_PCICOR_OFF);
	mdelay(2);

#endif

	if (HFA384X_INW(HFA384X_CMD_OFF) & HFA384X_CMD_BUSY) {
		printk(KERN_DEBUG "%s: COR sreset timeout\n", dev->name);
	}
}
