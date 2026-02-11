skip_mbi(FILE *infile) {
	int c;

	do {
		c = getc(infile);
		if (c < 0) return -1;
	} while (c & 0x80);

	return 0;
}
