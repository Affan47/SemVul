ne_probe(struct nic *nic, struct isa_device *isa) {
	int i;
	unsigned char c;
	unsigned char romdata[16];
	unsigned char testbuf[32];

	eth_vendor = VENDOR_NONE;
	eth_drain_receiver = 0;

	nic->irqno = 0;
	nic->ioaddr = isa->ioaddr;
	eth_nic_base = isa->ioaddr;


	if (eth_vendor == VENDOR_NONE) {

		static unsigned char test[] = "NE*000 memory";

		eth_bmem = 0;

		eth_flags = FLAG_PIO;
		eth_asic_base = eth_nic_base + NE_ASIC_OFFSET;
		eth_memsize = MEM_16384;
		eth_tx_start = 32;
		eth_rx_start = 32 + D8390_TXBUF_SIZE;
		c = inb(eth_asic_base + NE_RESET);
		outb(c, eth_asic_base + NE_RESET);
		(void) inb(0x84);
		outb(D8390_COMMAND_STP | D8390_COMMAND_RD2, eth_nic_base
				+ D8390_P0_COMMAND);
		outb(D8390_RCR_MON, eth_nic_base + D8390_P0_RCR);
		outb(D8390_DCR_FT1 | D8390_DCR_LS, eth_nic_base + D8390_P0_DCR);
		outb(MEM_8192, eth_nic_base + D8390_P0_PSTART);
		outb(MEM_16384, eth_nic_base + D8390_P0_PSTOP);
		eth_pio_write((unsigned char *) test, 8192, sizeof(test));
		eth_pio_read(8192, testbuf, sizeof(test));
		if (!memcmp(test, testbuf, sizeof(test)))
			goto out;
		eth_flags |= FLAG_16BIT;
		eth_memsize = MEM_32768;
		eth_tx_start = 64;
		eth_rx_start = 64 + D8390_TXBUF_SIZE;
		outb(D8390_DCR_WTS | D8390_DCR_FT1 | D8390_DCR_LS, eth_nic_base
				+ D8390_P0_DCR);
		outb(MEM_16384, eth_nic_base + D8390_P0_PSTART);
		outb(MEM_32768, eth_nic_base + D8390_P0_PSTOP);
		eth_pio_write((unsigned char *) test, 16384, sizeof(test));
		eth_pio_read(16384, testbuf, sizeof(test));
		if (!memcmp(testbuf, test, sizeof(test)))
			goto out;


out:
		if (eth_nic_base == 0)
			return (0);
		if (eth_nic_base > ISA_MAX_ADDR)
			eth_flags |= FLAG_16BIT;
		eth_vendor = VENDOR_NOVELL;
		eth_pio_read(0, romdata, sizeof(romdata));
		for (i = 0; i < ETH_ALEN; i++) {
			nic->node_addr[i] = romdata[i + ((eth_flags & FLAG_16BIT) ? i : 0)];
		}
		nic->ioaddr = eth_nic_base;
		DBG("\nNE%c000 base %4.4x, MAC Addr %s\n",
				(eth_flags & FLAG_16BIT) ? '2' : '1', eth_nic_base, eth_ntoa(
						nic->node_addr));
	}

	if (eth_vendor == VENDOR_NONE)
		return (0);

	if (eth_vendor != VENDOR_3COM)
		eth_rmem = eth_bmem;

	ne_reset(nic, isa);
	nic->nic_op = &ne_operations;
	return 1;
}
