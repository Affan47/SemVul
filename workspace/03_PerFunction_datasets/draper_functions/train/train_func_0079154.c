set_rid(const char *dev, u16 rid, int argc, char *argv[])
{
	u8 *data;
	int res, i;
	long int val;

	data = (u8 *) malloc(argc);
	if (data == NULL)
		return -1;

	for (i = 0; i < argc; i++) {
		val = strtol(argv[i], NULL, 16);
		if (val < 0 || val > 255) {
			usage();
			printf("\nInvalid data value '%s'\n", argv[i]);
			return -1;
		}
		data[i] = val;
	}

	res = hostapd_set_rid(dev, rid, data, argc, 1);
	if (res == EPERM) {
		printf("hostap_rid requires root privileges\n");
		return -1;
	}
	if (res) {
		printf("Could not communicate with the kernel driver.\n");
		return -1;
	}

	return 0;
}
