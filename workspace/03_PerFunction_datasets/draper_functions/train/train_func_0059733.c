getunimap(int fd, struct unimapdesc *ud0) {
	struct unimapdesc ud;
	int ct;

	ud.entry_ct = 0;
	ud.entries = 0;
	if (ioctl(fd, GIO_UNIMAP, &ud)) {
		if(errno != ENOMEM || ud.entry_ct == 0) {
			perror("GIO_UNIMAP(0)");
			return -1;
		}
		ct = ud.entry_ct;
		ud.entries = (struct unipair *)
			malloc(ct * sizeof(struct unipair));
		if (ud.entries == NULL) {
			fprintf(stderr, _("%s: out of memory\n"), progname);
			return -1;
		}
		if (ioctl(fd, GIO_UNIMAP, &ud)) {
			perror("GIO_UNIMAP");
			return -1;
		}
		if (ct != ud.entry_ct)
			fprintf(stderr,
				_("strange... ct changed from %d to %d\n"),
				ct, ud.entry_ct);


	}
	*ud0 = ud;
	return 0;
}
