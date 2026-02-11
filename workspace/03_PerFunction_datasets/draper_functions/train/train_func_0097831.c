appendseparator(FILE *fp, int seq, int utf8) {
	int n;

	if (utf8) {
		unsigned char u = (seq ? PSF2_STARTSEQ : PSF2_SEPARATOR);
		n = fwrite(&u, sizeof(u), 1, fp);
	} else {
		unsigned short u = (seq ? PSF1_STARTSEQ : PSF1_SEPARATOR);
		n = fwrite(&u, sizeof(u), 1, fp);
	}
	if (n != 1) {
		perror("appendseparator");
		exit(1);
	}
}
