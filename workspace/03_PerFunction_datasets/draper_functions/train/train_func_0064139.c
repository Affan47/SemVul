write_float(FILE* fout, float val) {
    if (fwrite(&val, sizeof(float), 1, fout) == 1) {
		return 0;
    } else {
		fprintf(stderr, "Couldn't write float: %s\n", strerror(errno));
		return 1;
    }
}
