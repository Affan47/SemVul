ns83820_setup_rx(struct nic *nic)
{
	unsigned i;
	ns->idle = 1;
	ns->next_rx = 0;
	ns->next_rx_desc = ns->descs;
	ns->next_empty = 0;
	ns->cur_rx = 0;


	for (i = 0; i < NR_RX_DESC; i++) {
		rx_ring[i].link = virt_to_le32desc(&rx_ring[i + 1]);
		rx_ring[i].bufptr =
		    virt_to_le32desc(&rxb[i * REAL_RX_BUF_SIZE]);
		rx_ring[i].cmdsts = cpu_to_le32(REAL_RX_BUF_SIZE);
		rx_ring[i].extsts = cpu_to_le32(0);
	}


	writel(0, ns->base + RXDP_HI);
	writel(virt_to_le32desc(&rx_ring[0]), ns->base + RXDP);

	dprintf(("starting receiver\n"));

	writel(0x0001, ns->base + CCSR);
	writel(0, ns->base + RFCR);
	writel(0x7fc00000, ns->base + RFCR);
	writel(0xffc00000, ns->base + RFCR);

	ns->up = 1;

	phy_intr(nic);


	ns->IMR_cache |= ISR_PHY;
	ns->IMR_cache |= ISR_RXRCMP;


	ns->IMR_cache |= ISR_RXORN;
	ns->IMR_cache |= ISR_RXSOVR;
	ns->IMR_cache |= ISR_RXDESC;
	ns->IMR_cache |= ISR_RXIDLE;
	ns->IMR_cache |= ISR_TXDESC;
	ns->IMR_cache |= ISR_TXIDLE;


	ns83820_set_multicast(nic);
	kick_rx();
}
