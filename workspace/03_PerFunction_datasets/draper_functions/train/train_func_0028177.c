do_command(uint16_t command, uint16_t seqnum, uint16_t varid, uint8_t *value, uint16_t length)
{
	unsigned char cp[254], rp[254];
	struct hci_request rq;
	uint8_t cmd[10];
	uint16_t size;

	size = (length < 8) ? 9 : ((length + 1) / 2) + 5;

	cmd[0] = command & 0xff;
	cmd[1] = command >> 8;
	cmd[2] = size & 0xff;
	cmd[3] = size >> 8;
	cmd[4] = seqnum & 0xff;
	cmd[5] = seqnum >> 8;
	cmd[6] = varid & 0xff;
	cmd[7] = varid >> 8;
	cmd[8] = 0x00;
	cmd[9] = 0x00;

	memset(cp, 0, sizeof(cp));
	cp[0] = 0xc2;
	memcpy(cp + 1, cmd, sizeof(cmd));
	memcpy(cp + 11, value, length);

	switch (varid) {
	case CSR_VARID_COLD_RESET:
	case CSR_VARID_WARM_RESET:
	case CSR_VARID_COLD_HALT:
	case CSR_VARID_WARM_HALT:
		return hci_send_cmd(dd, OGF_VENDOR_CMD, 0x00, (size * 2) + 1, cp);
	}

	memset(&rq, 0, sizeof(rq));
	rq.ogf    = OGF_VENDOR_CMD;
	rq.ocf    = 0x00;
	rq.event  = EVT_VENDOR;
	rq.cparam = cp;
	rq.clen   = (size * 2) + 1;
	rq.rparam = rp;
	rq.rlen   = sizeof(rp);

	if (hci_send_req(dd, &rq, 2000) < 0)
		return -1;

	if (rp[0] != 0xc2) {
		errno = EIO;
		return -1;
	}

	if ((rp[9] + (rp[10] << 8)) != 0) {
		errno = ENXIO;
		return -1;
	}

	memcpy(value, rp + 11, length);

	return 0;
}
