cmd_key(int dev_id, int argc, char **argv)
{
	struct hci_conn_info_req *cr;
	bdaddr_t bdaddr;
	int opt, dd;

	for_each_opt(opt, key_options, NULL) {
		switch (opt) {
		default:
			printf("%s", key_help);
			return;
		}
	}
	helper_arg(1, 1, &argc, &argv, key_help);

	str2ba(argv[0], &bdaddr);

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

	if (hci_change_link_key(dd, htobs(cr->conn_info->handle), 25000) < 0) {
		perror("Changing link key failed");
		exit(1);
	}

	free(cr);

	hci_close_dev(dd);
}
