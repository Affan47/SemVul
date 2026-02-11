cvtarc(num, arg)
	int             num;
	char           *arg[];
{
	struct heads    hdr;
	int             cvt;
	int             did[MAXARG];
	int             n;
	char           *makefnam();
	FILE           *fopen();

	if (arctemp)
		sprintf(tempname, "%s.CVT", arctemp);
	else
		makefnam("$ARCTEMP.CVT", arcname, tempname);
#if	!DOS
	image = 1;
#endif

	openarc(1);

	for (n = 0; n < num; n++)
		did[n] = 0;
	rempath(num, arg);

	if (num) {
		while (readhdr(&hdr, arc)) {
			cvt = 0;
			for (n = 0; n < num; n++) {

				if (match(hdr.name, arg[n])) {
					cvt = 1;
					did[n] = 1;
					break;
				}
			}

			if (cvt)
				cvtfile(&hdr);
			else {
				writehdr(&hdr, new);
				filecopy(arc, new, hdr.size);
			}
		}
	} else
		while (readhdr(&hdr, arc))
			cvtfile(&hdr);

	hdrver = 0;
	writehdr(&hdr, new);
	closearc(1);

	if (note) {
		for (n = 0; n < num; n++) {
			if (!did[n]) {
				printf("File not found: %s\n", arg[n]);
				nerrs++;
			}
		}
	}
}
