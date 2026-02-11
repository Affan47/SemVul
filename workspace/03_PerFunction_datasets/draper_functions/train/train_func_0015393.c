pkt_get_max_speed(struct pktcdvd_device *pd,
						unsigned *write_speed)
{
	struct packet_command cgc;
	struct request_sense sense;
	unsigned char buf[256+18];
	unsigned char *cap_buf;
	int ret, offset;

	cap_buf = &buf[sizeof(struct mode_page_header) + pd->mode_offset];
	init_cdrom_command(&cgc, buf, sizeof(buf), CGC_DATA_UNKNOWN);
	cgc.sense = &sense;

	ret = pkt_mode_sense(pd, &cgc, GPMODE_CAPABILITIES_PAGE, 0);
	if (ret) {
		cgc.buflen = pd->mode_offset + cap_buf[1] + 2 +
			     sizeof(struct mode_page_header);
		ret = pkt_mode_sense(pd, &cgc, GPMODE_CAPABILITIES_PAGE, 0);
		if (ret) {
			pkt_dump_sense(pd, &cgc);
			return ret;
		}
	}

	offset = 20;
	if (cap_buf[1] >= 28)
		offset = 28;
	if (cap_buf[1] >= 30) {


		int num_spdb = (cap_buf[30] << 8) + cap_buf[31];
		if (num_spdb > 0)
			offset = 34;
	}

	*write_speed = (cap_buf[offset] << 8) | cap_buf[offset + 1];
	return 0;
}
