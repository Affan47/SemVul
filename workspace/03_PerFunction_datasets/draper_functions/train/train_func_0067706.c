ne2k_pci_get_8390_hdr(struct net_device *dev, struct e8390_pkt_hdr *hdr, int ring_page)
{

	long nic_base = dev->base_addr;


	if (ei_status.dmaing) {
		netdev_err(dev, "DMAing conflict in ne2k_pci_get_8390_hdr "
			   "[DMAstat:%d][irqlock:%d].\n",
			   ei_status.dmaing, ei_status.irqlock);
		return;
	}

	ei_status.dmaing |= 0x01;
	outb(E8390_NODMA+E8390_PAGE0+E8390_START, nic_base+ NE_CMD);
	outb(sizeof(struct e8390_pkt_hdr), nic_base + EN0_RCNTLO);
	outb(0, nic_base + EN0_RCNTHI);
	outb(0, nic_base + EN0_RSARLO);
	outb(ring_page, nic_base + EN0_RSARHI);
	outb(E8390_RREAD+E8390_START, nic_base + NE_CMD);

	if (ei_status.ne2k_flags & ONLY_16BIT_IO) {
		insw(NE_BASE + NE_DATAPORT, hdr, sizeof(struct e8390_pkt_hdr)>>1);
	} else {
		*(u32*)hdr = le32_to_cpu(inl(NE_BASE + NE_DATAPORT));
		le16_to_cpus(&hdr->count);
	}

	outb(ENISR_RDC, nic_base + EN0_ISR);
	ei_status.dmaing &= ~0x01;
}
