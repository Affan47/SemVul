eepro_transmit(
	struct nic *nic,
	const char *d,
	unsigned int t,
	unsigned int s,
	const char *p)
{
	unsigned int	status, tx_available, last, end, length;
	unsigned short	type;
	int		boguscount = 20;

	length = s + ETH_HLEN;
	if (tx_end > tx_start)
		tx_available = XMT_RAM - (tx_end - tx_start);
	else if (tx_end < tx_start)
		tx_available = tx_start - tx_end;
	else
		tx_available = XMT_RAM;
	assert ( length <= tx_available );
	last = tx_end;
	end = last + (((length + 3) >> 1) << 1) + XMT_HEADER;
	if (end >= (XMT_UPPER_LIMIT << 8)) {
		last = (XMT_LOWER_LIMIT << 8);
		end = last + (((length + 3) >> 1) << 1) + XMT_HEADER;
	}
	outw(last, nic->ioaddr + HOST_ADDRESS_REG);
	outw(XMT_CMD, nic->ioaddr + IO_PORT);
	outw(0, nic->ioaddr + IO_PORT);
	outw(end, nic->ioaddr + IO_PORT);
	outw(length, nic->ioaddr + IO_PORT);
	outsw(nic->ioaddr + IO_PORT, d, ETH_ALEN / 2);
	outsw(nic->ioaddr + IO_PORT, nic->node_addr, ETH_ALEN / 2);
	type = htons(t);
	outsw(nic->ioaddr + IO_PORT, &type, sizeof(type) / 2);
	outsw(nic->ioaddr + IO_PORT, p, (s + 3) >> 1);

	status = inw(nic->ioaddr + IO_PORT);
	outw(last, nic->ioaddr + xmt_bar);
	outb(XMT_CMD, nic->ioaddr);
	tx_start = last;
	tx_last = last;
	tx_end = end;
#if	0
	printf("%d %d\n", tx_start, tx_end);
#endif
	while (boguscount > 0) {
		if (((status = inw(nic->ioaddr + IO_PORT)) & TX_DONE_BIT) == 0) {
			udelay(40);
			boguscount--;
			continue;
		}
		if ((status & 0x2000) == 0) {
			DBG("Transmit status %hX\n", status);
		}
	}
}
