cmd_encrypt(int ctl, int hdev, char *opt)
{
	struct hci_dev_req dr;

	dr.dev_id = hdev;
	if (!strcmp(opt, "encrypt"))
		dr.dev_opt = ENCRYPT_P2P;
	else
		dr.dev_opt = ENCRYPT_DISABLED;

	if (ioctl(ctl, HCISETENCRYPT, (unsigned long) &dr) < 0) {
		fprintf(stderr, "Can't set encrypt on hci%d: %s (%d)\n",
						hdev, strerror(errno), errno);
		exit(1);
	}
}
