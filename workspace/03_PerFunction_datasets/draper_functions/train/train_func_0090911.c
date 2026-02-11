om_text_print_bidimentional_map(FILE *fp, int xlen, int ylen,
			char **xlabel, char **ylabel, int *value)
{
	char *asciipal = " .-+#";
	int pallen = strlen(asciipal);
	int x, y, l, max = 0;


	l = xlen*ylen;
	for (x = 0; x < l; x++)
		if (max < value[x])
			max = value[x];
	if (max == 0) max++;

	for (y = 0; y < ylen; y++) {
		fprintf(fp, "%15s: ", ylabel[y]);
		for (x = 0; x < xlen; x++) {
			int coloridx;
			int val = value[(y*xlen)+x];

			coloridx = ((pallen-1)*val)/max;
			fputc(asciipal[coloridx], fp);
		}
		fprintf(fp, "\n");
	}
	fprintf(fp, "\n");

	{
		char **p = malloc(sizeof(char*)*xlen);


		for (x = 0; x < xlen; x++)
			p[x] = xlabel[x];
		while(1) {
			int sentinel = 0;
			fprintf(fp, "%15s  ", "");
			for (x = 0; x < xlen; x++) {
				if (*(p[x]) != '\0') {
					fputc(*(p[x]), fp);
					p[x]++;
					sentinel++;
				} else {
					fputc(' ', fp);
				}
			}
			fputc('\n', fp);
			if (sentinel == 0) break;
		}
		free(p);
	}
}
