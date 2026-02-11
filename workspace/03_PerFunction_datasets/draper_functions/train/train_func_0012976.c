AX88190_init(struct net_device *dev, int startp)
{
	struct axnet_dev *info = PRIV(dev);
	long e8390_base = dev->base_addr;
	struct ei_device *ei_local = netdev_priv(dev);
	int i;
	int endcfg = ei_local->word16 ? (0x48 | ENDCFG_WTS) : 0x48;

	if(sizeof(struct e8390_pkt_hdr)!=4)
    		panic("8390.c: header struct mispacked\n");

	outb_p(E8390_NODMA+E8390_PAGE0+E8390_STOP, e8390_base+E8390_CMD);
	outb_p(endcfg, e8390_base + EN0_DCFG);

	outb_p(0x00,  e8390_base + EN0_RCNTLO);
	outb_p(0x00,  e8390_base + EN0_RCNTHI);

	outb_p(E8390_RXOFF|0x40, e8390_base + EN0_RXCR);
	outb_p(E8390_TXOFF, e8390_base + EN0_TXCR);

	outb_p(ei_local->tx_start_page, e8390_base + EN0_TPSR);
	ei_local->tx1 = ei_local->tx2 = 0;
	outb_p(ei_local->rx_start_page, e8390_base + EN0_STARTPG);
	outb_p(ei_local->stop_page-1, e8390_base + EN0_BOUNDARY);
	ei_local->current_page = ei_local->rx_start_page;
	outb_p(ei_local->stop_page, e8390_base + EN0_STOPPG);

	outb_p(0xFF, e8390_base + EN0_ISR);
	outb_p(0x00,  e8390_base + EN0_IMR);


	outb_p(E8390_NODMA + E8390_PAGE1 + E8390_STOP, e8390_base+E8390_CMD);
	for(i = 0; i < 6; i++)
	{
		outb_p(dev->dev_addr[i], e8390_base + EN1_PHYS_SHIFT(i));
		if(inb_p(e8390_base + EN1_PHYS_SHIFT(i))!=dev->dev_addr[i])
			netdev_err(dev, "Hw. address read/write mismap %d\n", i);
	}

	outb_p(ei_local->rx_start_page, e8390_base + EN1_CURPAG);
	outb_p(E8390_NODMA+E8390_PAGE0+E8390_STOP, e8390_base+E8390_CMD);

	netif_start_queue(dev);
	ei_local->tx1 = ei_local->tx2 = 0;
	ei_local->txing = 0;

	if (info->flags & IS_AX88790)
		outb(0x10, e8390_base + AXNET_GPIO);

	if (startp)
	{
		outb_p(0xff,  e8390_base + EN0_ISR);
		outb_p(ENISR_ALL,  e8390_base + EN0_IMR);
		outb_p(E8390_NODMA+E8390_PAGE0+E8390_START, e8390_base+E8390_CMD);
		outb_p(E8390_TXCONFIG | info->duplex_flag,
		       e8390_base + EN0_TXCR);

		outb_p(E8390_RXCONFIG | 0x40, e8390_base + EN0_RXCR);
		do_set_multicast_list(dev);
	}
}
