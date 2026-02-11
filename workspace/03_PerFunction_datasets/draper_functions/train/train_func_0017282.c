pkt_set_write_settings(struct pktcdvd_device *pd)
{
	struct packet_command cgc;
	struct request_sense sense;
	write_param_page *wp;
	char buffer[128];
	int ret, size;


	if ((pd->mmc3_profile == 0x1a) || (pd->mmc3_profile == 0x12))
		return 0;

	memset(buffer, 0, sizeof(buffer));
	init_cdrom_command(&cgc, buffer, sizeof(*wp), CGC_DATA_READ);
	cgc.sense = &sense;
	if ((ret = pkt_mode_sense(pd, &cgc, GPMODE_WRITE_PARMS_PAGE, 0))) {
		pkt_dump_sense(pd, &cgc);
		return ret;
	}

	size = 2 + ((buffer[0] << 8) | (buffer[1] & 0xff));
	pd->mode_offset = (buffer[6] << 8) | (buffer[7] & 0xff);
	if (size > sizeof(buffer))
		size = sizeof(buffer);


	init_cdrom_command(&cgc, buffer, size, CGC_DATA_READ);
	cgc.sense = &sense;
	if ((ret = pkt_mode_sense(pd, &cgc, GPMODE_WRITE_PARMS_PAGE, 0))) {
		pkt_dump_sense(pd, &cgc);
		return ret;
	}


	wp = (write_param_page *) &buffer[sizeof(struct mode_page_header) + pd->mode_offset];

	wp->fp = pd->settings.fp;
	wp->track_mode = pd->settings.track_mode;
	wp->write_type = pd->settings.write_type;
	wp->data_block_type = pd->settings.block_mode;

	wp->multi_session = 0;

#ifdef PACKET_USE_LS
	wp->link_size = 7;
	wp->ls_v = 1;
#endif

	if (wp->data_block_type == PACKET_BLOCK_MODE1) {
		wp->session_format = 0;
		wp->subhdr2 = 0x20;
	} else if (wp->data_block_type == PACKET_BLOCK_MODE2) {
		wp->session_format = 0x20;
		wp->subhdr2 = 8;
#if 0
		wp->mcn[0] = 0x80;
		memcpy(&wp->mcn[1], PACKET_MCN, sizeof(wp->mcn) - 1);
#endif
	} else {


		pkt_err(pd, "write mode wrong %d\n", wp->data_block_type);
		return 1;
	}
	wp->packet_size = cpu_to_be32(pd->settings.size >> 2);

	cgc.buflen = cgc.cmd[8] = size;
	if ((ret = pkt_mode_select(pd, &cgc))) {
		pkt_dump_sense(pd, &cgc);
		return ret;
	}

	pkt_print_settings(pd);
	return 0;
}
