cmd_cmd(int dev_id, int argc, char **argv)
{
	unsigned char buf[HCI_MAX_EVENT_SIZE], *ptr = buf;
	struct hci_filter flt;
	hci_event_hdr *hdr;
	int i, opt, len, dd;
	uint16_t ocf;
	uint8_t ogf;

	for_each_opt(opt, cmd_options, NULL) {
		switch (opt) {
		default:
			printf("%s", cmd_help);
			return;
		}
	}
	helper_arg(2, -1, &argc, &argv, cmd_help);

	if (dev_id < 0)
		dev_id = hci_get_route(NULL);

	errno = 0;
	ogf = strtol(argv[0], NULL, 16);
	ocf = strtol(argv[1], NULL, 16);
	if (errno == ERANGE || (ogf > 0x3f) || (ocf > 0x3ff)) {
		printf("%s", cmd_help);
		return;
	}

	for (i = 2, len = 0; i < argc && len < (int) sizeof(buf); i++, len++)
		*ptr++ = (uint8_t) strtol(argv[i], NULL, 16);

	dd = hci_open_dev(dev_id);
	if (dd < 0) {
		perror("Device open failed");
		exit(EXIT_FAILURE);
	}


	hci_filter_clear(&flt);
	hci_filter_set_ptype(HCI_EVENT_PKT, &flt);
	hci_filter_all_events(&flt);
	if (setsockopt(dd, SOL_HCI, HCI_FILTER, &flt, sizeof(flt)) < 0) {
		perror("HCI filter setup failed");
		exit(EXIT_FAILURE);
	}

	printf("< HCI Command: ogf 0x%02x, ocf 0x%04x, plen %d\n", ogf, ocf, len);
	hex_dump("  ", 20, buf, len); fflush(stdout);

	if (hci_send_cmd(dd, ogf, ocf, len, buf) < 0) {
		perror("Send failed");
		exit(EXIT_FAILURE);
	}

	len = read(dd, buf, sizeof(buf));
	if (len < 0) {
		perror("Read failed");
		exit(EXIT_FAILURE);
	}

	hdr = (void *)(buf + 1);
	ptr = buf + (1 + HCI_EVENT_HDR_SIZE);
	len -= (1 + HCI_EVENT_HDR_SIZE);

	printf("> HCI Event: 0x%02x plen %d\n", hdr->evt, hdr->plen);
	hex_dump("  ", 20, ptr, len); fflush(stdout);

	hci_close_dev(dd);
}
