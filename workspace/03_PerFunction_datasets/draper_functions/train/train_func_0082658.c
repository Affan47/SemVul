bin2c_table(int size, FILE *in, FILE *out)
{
	char buf[BUFSIZE];
	size_t s = sizeof buf;
	int i, j=0;
	char elem[16];

	while ((s = fread(buf, 1, s, in))) {
		for (i = 0; i < s; i++) {
			int elemlen;
			if (i % CHARS_PER_LINE == 0) {
				fputs("\t", out);
			}
			char2cchar(elem, buf[i]);
			elemlen = strlen(elem);
			fputs(elem, out);
			if (j+1 < size) {
				int k;
				fputs(",", out);
				for (k=0; k<4-elemlen; k++) fputs(" ", out);
				if ((j+1) % CHARS_PER_LINE == 0) {
					fputs("\n", out);
				}
			} else {
				fputs("\n", out);
			}
			j++;
		}
	}
}
