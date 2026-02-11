dmfe_poll(struct nic *nic, int retrieve)
{
	u32 rdes0;
	int entry = db->cur_rx % RX_DESC_CNT;
	int rxlen;
	rdes0 = le32_to_cpu(rxd[entry].rdes0);
	if (rdes0 & 0x80000000)
		return 0;

	if (!retrieve)
		return 1;

	if ((rdes0 & 0x300) != 0x300) {

		printf("strange Packet\n");
		rxd[entry].rdes0 = cpu_to_le32(0x80000000);
		return 0;
	} else {

		rxlen = ((rdes0 >> 16) & 0x3fff) - 4;

		if (rdes0 & 0x8000) {
			printf("Error\n");
			return 0;
		}
		if (!(rdes0 & 0x8000) ||
		    ((db->cr6_data & CR6_PM) && (rxlen > 6))) {
			if (db->dm910x_chk_mode & 1)
				printf("Silly check mode\n");

			nic->packetlen = rxlen;
			memcpy(nic->packet, rxb + (entry * RX_ALLOC_SIZE),
			       nic->packetlen);
		}
	}
	rxd[entry].rdes0 = cpu_to_le32(0x80000000);
	db->cur_rx++;
	return 1;
}
