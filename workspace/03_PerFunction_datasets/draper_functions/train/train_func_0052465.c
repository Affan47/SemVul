cmd_down(int ctl, int hdev, char *opt)
{

	if (ioctl(ctl, HCIDEVDOWN, hdev) < 0) {
		fprintf(stderr, "Can't down device hci%d: %s (%d)\n",
						hdev, strerror(errno), errno);
		exit(1);
	}
}
