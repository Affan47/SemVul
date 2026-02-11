main(int argc, char *argv[])
{
	int opt, ctl, i, cmd = 0;

	while ((opt = getopt_long(argc, argv, "ah", main_options, NULL)) != -1) {
		switch (opt) {
		case 'a':
			all = 1;
			break;

		case 'h':
		default:
			usage();
			exit(0);
		}
	}

	argc -= optind;
	argv += optind;
	optind = 0;


	if ((ctl = socket(AF_BLUETOOTH, SOCK_RAW, BTPROTO_HCI)) < 0) {
		perror("Can't open HCI socket.");
		exit(1);
	}

	if (argc < 1) {
		print_dev_list(ctl, 0);
		exit(0);
	}

	di.dev_id = atoi(argv[0] + 3);
	argc--; argv++;

	if (ioctl(ctl, HCIGETDEVINFO, (void *) &di)) {
		perror("Can't get device info");
		exit(1);
	}

	if (hci_test_bit(HCI_RAW, &di.flags) &&
			!bacmp(&di.bdaddr, BDADDR_ANY)) {
		int dd = hci_open_dev(di.dev_id);
		hci_read_bd_addr(dd, &di.bdaddr, 1000);
		hci_close_dev(dd);
	}

	while (argc > 0) {
		for (i = 0; command[i].cmd; i++) {
			if (strncmp(command[i].cmd,
					*argv, strlen(command[i].cmd)))
				continue;

			if (command[i].opt) {
				argc--; argv++;
			}

			command[i].func(ctl, di.dev_id, *argv);
			cmd = 1;
			break;
		}

		if (command[i].cmd == 0)
			fprintf(stderr, "Warning: unknown command - \"%s\"\n",
					*argv);

		argc--; argv++;
	}

	if (!cmd)
		print_dev_info(ctl, &di);

	close(ctl);
	return 0;
}
