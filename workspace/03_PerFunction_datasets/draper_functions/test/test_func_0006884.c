copy_file(const char* infn, const char* outfn) {
	FILE* fin = fopen(infn, "rb");
	FILE* fout = fopen(outfn, "wb");
	struct stat st;
	off_t len;
	if (!fin) {
		SYSERROR("Failed to open xyls file \"%s\" for copying", infn);
		return -1;
	}
	if (stat(infn, &st)) {
		SYSERROR("Failed to stat file \"%s\"", infn);
		return -1;
	}
	len = st.st_size;
	if (!fout) {
		SYSERROR("Failed to open output xyls file \"%s\" for copying", outfn);
		return -1;
	}
	if (pipe_file_offset(fin, 0, len, fout)) {
		ERROR("Failed to copy xyls file \"%s\" to \"%s\"", infn, outfn);
		return -1;
	}
	if (fclose(fin)) {
		SYSERROR("Failed to close input file \"%s\"", infn);
		return -1;
	}
	if (fclose(fout)) {
		SYSERROR("Failed to close output file \"%s\"", outfn);
		return -1;
	}
	return 0;
}
