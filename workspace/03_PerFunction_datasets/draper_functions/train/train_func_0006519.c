cmd_block(int ctl, int hdev, char *opt)
{
	bdaddr_t bdaddr;
	int dd;

	if (!opt)
		return;

	dd = hci_open_dev(hdev);
	if (dd < 0) {
		fprintf(stderr, "Can't open device hci%d: %s (%d)\n",
						hdev, strerror(errno), errno);
		exit(1);
	}

	str2ba(opt, &bdaddr);

	if (ioctl(dd, HCIBLOCKADDR, &bdaddr) < 0) {
		perror("ioctl(HCIBLOCKADDR)");
		exit(1);
	}

	hci_close_dev(dd);
}
