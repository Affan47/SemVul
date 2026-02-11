getoldunicodemap(void) {
	struct unimapdesc descr;

	if (getunimap(fd, &descr))
		leave(1);
	ounimap = descr;
	have_ounimap = 1;
}
