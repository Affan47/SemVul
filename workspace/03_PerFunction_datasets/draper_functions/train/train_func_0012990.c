ne2k_pci_block_output(struct net_device *dev, int count,
				  const unsigned char *buf, const int start_page)
{
	long nic_base = NE_BASE;
	unsigned long dma_start;


	if (ei_status.ne2k_flags & ONLY_32BIT_IO)
		count = (count + 3) & 0xFFFC;
	else
		if (count & 0x01)
			count++;


	if (ei_status.dmaing) {
		netdev_err(dev, "DMAing conflict in ne2k_pci_block_output."
			   "[DMAstat:%d][irqlock:%d]\n",
			   ei_status.dmaing, ei_status.irqlock);
		return;
	}
	ei_status.dmaing |= 0x01;

	outb(E8390_PAGE0+E8390_START+E8390_NODMA, nic_base + NE_CMD);

#ifdef NE8390_RW_BUGFIX


	outb(0x42, nic_base + EN0_RCNTLO);
	outb(0x00, nic_base + EN0_RCNTHI);
	outb(0x42, nic_base + EN0_RSARLO);
	outb(0x00, nic_base + EN0_RSARHI);
	outb(E8390_RREAD+E8390_START, nic_base + NE_CMD);
#endif
	outb(ENISR_RDC, nic_base + EN0_ISR);


	outb(count & 0xff, nic_base + EN0_RCNTLO);
	outb(count >> 8,   nic_base + EN0_RCNTHI);
	outb(0x00, nic_base + EN0_RSARLO);
	outb(start_page, nic_base + EN0_RSARHI);
	outb(E8390_RWRITE+E8390_START, nic_base + NE_CMD);
	if (ei_status.ne2k_flags & ONLY_16BIT_IO) {
		outsw(NE_BASE + NE_DATAPORT, buf, count>>1);
	} else {
		outsl(NE_BASE + NE_DATAPORT, buf, count>>2);
		if (count & 3) {
			buf += count & ~3;
			if (count & 2) {
				__le16 *b = (__le16 *)buf;

				outw(le16_to_cpu(*b++), NE_BASE + NE_DATAPORT);
				buf = (char *)b;
			}
		}
	}

	dma_start = jiffies;

	while ((inb(nic_base + EN0_ISR) & ENISR_RDC) == 0)
		if (jiffies - dma_start > 2) {
			netdev_warn(dev, "timeout waiting for Tx RDC.\n");
			ne2k_pci_reset_8390(dev);
			NS8390_init(dev,1);
			break;
		}

	outb(ENISR_RDC, nic_base + EN0_ISR);
	ei_status.dmaing &= ~0x01;
}
