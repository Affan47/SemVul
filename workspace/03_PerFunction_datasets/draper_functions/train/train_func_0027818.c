solvedfile_set_file(char* fn, anbool* vals, int N) {
	FILE* f;
	int i;


	for (i=0; i<N; i++)
		if (vals[i]) vals[i] = TRUE;
		else vals[i] = FALSE;

	f = fopen(fn, "wb");
	if (!f) {
		SYSERROR("Failed to open file \"%s\" for writing", fn);
		return -1;
	}
	if ((fwrite(vals, 1, N, f) != N) ||
		fclose(f)) {
		SYSERROR("Failed to write solved file \"%s\"", fn);
		return -1;
	}
	return 0;
}
