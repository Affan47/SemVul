format_disk(int ctrl)
{
	struct format_descr descr;
	unsigned int track;

	printf(_("Formatting ... "));
	fflush(stdout);
	if (ioctl(ctrl, FDFMTBEG, NULL) < 0)
		err(EXIT_FAILURE, "ioctl: FDFMTBEG");
	for (track = 0; track < param.track; track++) {
		descr.track = track;
		descr.head = 0;
		if (ioctl(ctrl, FDFMTTRK, (long) &descr) < 0)
			err(EXIT_FAILURE, "ioctl: FDFMTTRK");

		printf("%3d\b\b\b", track);
		fflush(stdout);
		if (param.head == 2) {
			descr.head = 1;
			if (ioctl(ctrl, FDFMTTRK, (long)&descr) < 0)
				err(EXIT_FAILURE, "ioctl: FDFMTTRK");
		}
	}
	if (ioctl(ctrl, FDFMTEND, NULL) < 0)
		err(EXIT_FAILURE, "ioctl: FDFMTEND");
	printf(_("done\n"));
}
