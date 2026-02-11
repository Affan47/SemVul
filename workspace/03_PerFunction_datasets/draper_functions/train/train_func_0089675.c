hci_read_transmit_power_level(int dd, uint16_t handle, uint8_t type,
					int8_t *level, int to)
{
	read_transmit_power_level_cp cp;
	read_transmit_power_level_rp rp;
	struct hci_request rq;

	memset(&cp, 0, sizeof(cp));
	cp.handle = handle;
	cp.type   = type;

	memset(&rq, 0, sizeof(rq));
	rq.ogf    = OGF_HOST_CTL;
	rq.ocf    = OCF_READ_TRANSMIT_POWER_LEVEL;
	rq.cparam = &cp;
	rq.clen   = READ_TRANSMIT_POWER_LEVEL_CP_SIZE;
	rq.rparam = &rp;
	rq.rlen   = READ_TRANSMIT_POWER_LEVEL_RP_SIZE;

	if (hci_send_req(dd, &rq, to) < 0)
		return -1;

	if (rp.status) {
		errno = EIO;
		return -1;
	}

	*level = rp.level;
	return 0;
}
