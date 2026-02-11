tg3_get_device_address(struct tg3 *tp)
{
	struct nic *nic = tp->nic;
	uint32_t hi, lo, mac_offset;

	if (PCI_FUNC(tp->pdev->busdevfn) == 0)
		mac_offset = 0x7c;
	else
		mac_offset = 0xcc;


	tg3_read_mem(NIC_SRAM_MAC_ADDR_HIGH_MBOX, &hi);
	if ((hi >> 16) == 0x484b) {
		nic->node_addr[0] = (hi >>  8) & 0xff;
		nic->node_addr[1] = (hi >>  0) & 0xff;

		tg3_read_mem(NIC_SRAM_MAC_ADDR_LOW_MBOX, &lo);
		nic->node_addr[2] = (lo >> 24) & 0xff;
		nic->node_addr[3] = (lo >> 16) & 0xff;
		nic->node_addr[4] = (lo >>  8) & 0xff;
		nic->node_addr[5] = (lo >>  0) & 0xff;
	}

	else if (!tg3_nvram_read(tp, mac_offset + 0, &hi) &&
		 !tg3_nvram_read(tp, mac_offset + 4, &lo)) {
		nic->node_addr[0] = ((hi >> 16) & 0xff);
		nic->node_addr[1] = ((hi >> 24) & 0xff);
		nic->node_addr[2] = ((lo >>  0) & 0xff);
		nic->node_addr[3] = ((lo >>  8) & 0xff);
		nic->node_addr[4] = ((lo >> 16) & 0xff);
		nic->node_addr[5] = ((lo >> 24) & 0xff);
	}

	else {
		hi = tr32(MAC_ADDR_0_HIGH);
		lo = tr32(MAC_ADDR_0_LOW);

		nic->node_addr[5] = lo & 0xff;
		nic->node_addr[4] = (lo >> 8) & 0xff;
		nic->node_addr[3] = (lo >> 16) & 0xff;
		nic->node_addr[2] = (lo >> 24) & 0xff;
		nic->node_addr[1] = hi & 0xff;
		nic->node_addr[0] = (hi >> 8) & 0xff;
	}

	return 0;
}
