com20020_found(struct net_device *dev, int shared)
{
	struct arcnet_local *lp;
	int ioaddr = dev->base_addr;


	lp = netdev_priv(dev);

	lp->hw.owner = THIS_MODULE;
	lp->hw.command = com20020_command;
	lp->hw.status = com20020_status;
	lp->hw.intmask = com20020_setmask;
	lp->hw.reset = com20020_reset;
	lp->hw.copy_to_card = com20020_copy_to_card;
	lp->hw.copy_from_card = com20020_copy_from_card;
	lp->hw.close = com20020_close;


	if (!dev->dev_addr[0])
		dev->dev_addr[0] = arcnet_inb(ioaddr, 8);

	com20020_set_subaddress(lp, ioaddr, SUB_SETUP1);
	arcnet_outb(lp->setup, ioaddr, COM20020_REG_W_XREG);

	if (lp->card_flags & ARC_CAN_10MBIT) {
		com20020_set_subaddress(lp, ioaddr, SUB_SETUP2);
		arcnet_outb(lp->setup2, ioaddr, COM20020_REG_W_XREG);


		mdelay(1);
		arcnet_outb(STARTIOcmd, ioaddr, COM20020_REG_W_COMMAND);
	}

	lp->config = (lp->timeout << 3) | (lp->backplane << 2) | SUB_NODE;

	arcnet_outb(lp->config, ioaddr, COM20020_REG_W_CONFIG);
	arcnet_outb(dev->dev_addr[0], ioaddr, COM20020_REG_W_XREG);


	if (request_irq(dev->irq, arcnet_interrupt, shared,
			"arcnet (COM20020)", dev)) {
		arc_printk(D_NORMAL, dev, "Can't get IRQ %d!\n", dev->irq);
		return -ENODEV;
	}

	dev->base_addr = ioaddr;

	arc_printk(D_NORMAL, dev, "%s: station %02Xh found at %03lXh, IRQ %d.\n",
		   lp->card_name, dev->dev_addr[0], dev->base_addr, dev->irq);

	if (lp->backplane)
		arc_printk(D_NORMAL, dev, "Using backplane mode.\n");

	if (lp->timeout != 3)
		arc_printk(D_NORMAL, dev, "Using extended timeout value of %d\n",
			   lp->timeout);

	arc_printk(D_NORMAL, dev, "Using CKP %d - data rate %s\n",
		   lp->setup >> 1,
		   clockrates[3 -
			      ((lp->setup2 & 0xF0) >> 4) +
			      ((lp->setup & 0x0F) >> 1)]);


	if (register_netdev(dev)) {
		free_irq(dev->irq, dev);
		return -EIO;
	}
	return 0;
}
