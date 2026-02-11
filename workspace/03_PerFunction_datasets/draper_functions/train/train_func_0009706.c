solvedfile_getsize(char* fn) {
	FILE* f;
	off_t end;
	f = fopen(fn, "rb");
	if (!f) {
		return -1;
	}
	if (fseek(f, 0, SEEK_END) ||
		((end = ftello(f)) == -1)) {
		fprintf(stderr, "Error: seeking to end of file %s: %s\n",
				fn, strerror(errno));
		fclose(f);
		return -1;
	}
	return (int)end;
}
