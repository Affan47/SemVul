solvedfile_getall_val(char* fn, int firstfield, int lastfield, int maxfields, int val) {
	FILE* f;
	off_t end;
	int fields = 0;
	il* list;
	int i;
	unsigned char* map;

	list = il_new(256);

	f = fopen(fn, "rb");
	if (!f) {

		if (val == 0) {
			for (i=firstfield; i<=lastfield; i++) {
				il_append(list, i);
				fields++;
				if (fields == maxfields)
					break;
			}
		}
		return list;
	}

	if (fseek(f, 0, SEEK_END) ||
		((end = ftello(f)) == -1)) {
		fprintf(stderr, "Error: seeking to end of file %s: %s\n",
				fn, strerror(errno));
		fclose(f);
		il_free(list);
		return NULL;
	}

    firstfield--;
    lastfield--;
	if (end <= firstfield) {
		fclose(f);
		return list;
	}

	map = mmap(NULL, end, PROT_READ, MAP_SHARED, fileno(f), 0);
	fclose(f);
	if (map == MAP_FAILED) {
		fprintf(stderr, "Error: couldn't mmap file %s: %s\n", fn, strerror(errno));
		il_free(list);
		return NULL;
	}

	for (i=firstfield; ((lastfield == -1) || (i<=lastfield)) && (i < end); i++) {
		if (map[i] == val) {

			il_append(list, i+1);
			if (il_size(list) == maxfields)
				break;
		}
	}

	munmap(map, end);

	if (val == 0) {

		for (i=end; i<=lastfield; i++) {
			if (il_size(list) == maxfields)
				break;

			il_append(list, i+1);
		}
	}
	return list;
}
