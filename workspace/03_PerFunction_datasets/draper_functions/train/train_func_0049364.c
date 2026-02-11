cmd_tpl(int dev_id, int argc, char **argv)
{
	struct hci_conn_info_req *cr;
	bdaddr_t bdaddr;
	uint8_t type;
	int8_t level;
	int opt, dd;

	for_each_opt(opt, tpl_options, NULL) {
		switch (opt) {
		default:
			printf("%s", tpl_help);
			return;
		}
	}
	helper_arg(1, 2, &argc, &argv, tpl_help);

	str2ba(argv[0], &bdaddr);
	type = (argc > 1) ? atoi(argv[1]) : 0;

	if (dev_id < 0) {
		dev_id = hci_for_each_dev(HCI_UP, find_conn, (long) &bdaddr);
		if (dev_id < 0) {
			fprintf(stderr, "Not connected.\n");
			exit(1);
		}
	}

	dd = hci_open_dev(dev_id);
	if (dd < 0) {
		perror("HCI device open failed");
		exit(1);
	}

	cr = malloc(sizeof(*cr) + sizeof(struct hci_conn_info));
	if (!cr) {
		perror("Can't allocate memory");
		exit(1);
	}

	bacpy(&cr->bdaddr, &bdaddr);
	cr->type = ACL_LINK;
	if (ioctl(dd, HCIGETCONNINFO, (unsigned long) cr) < 0) {
		perror("Get connection info failed");
		exit(1);
	}

	if (hci_read_transmit_power_level(dd, htobs(cr->conn_info->handle), type, &level, 1000) < 0) {
		perror("HCI read transmit power level request failed");
		exit(1);
	}

	printf("%s transmit power level: %d\n",
		(type == 0) ? "Current" : "Maximum", level);

	free(cr);

	hci_close_dev(dd);
}
