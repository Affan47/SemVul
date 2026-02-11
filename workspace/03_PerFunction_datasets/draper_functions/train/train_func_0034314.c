parse_headers(FILE *bmpfile) {
	int c;
	int exttype;

	clear_extparms();

	c = getc(bmpfile);
	if (c < 0) return -1;
	if (!(c & 0x80)) {

		return 0;
	}
	exttype = (c >> 5) & 0x03;


	switch (exttype) {
		case 0:


			if (skip_mbi(bmpfile) < 0) return -1;
			break;
		case 1: case 2:

			return -1;
		case 3:

			do {
				int namelen, valuelen;
				char *name, *value;
				c = getc(bmpfile);
				if (c < 0) return -1;

				namelen = (c >> 4) & 0x07;
				name = malloc(namelen + 1);
				if (!name) return -1;
				if (fread(name, namelen, 1, bmpfile) < (size_t) namelen)
					return -1;

				valuelen = c & 0x0f;
				value = malloc(valuelen + 1);
				if (!value) { free(name); return -1; }
				if (fread(value, valuelen, 1, bmpfile) < (size_t) valuelen)
					return -1;

				new_extparm(name, value);
			} while (c & 0x80);
			break;
	}
	return 0;
}
