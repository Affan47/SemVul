meta_id3v1_delete(char * filename) {

	FILE * file;
	unsigned char id3v1_file[128];
	long pos;

	if ((file = fopen(filename, "r+b")) == NULL) {
		fprintf(stderr, "meta_id3v1_delete: fopen() failed\n");
		return META_ERROR_NOT_WRITABLE;
	}

	if (fseek(file, -128L, SEEK_END) != 0) {
		fprintf(stderr, "meta_id3v1_delete: fseek() failed\n");
		fclose(file);
		return META_ERROR_INTERNAL;
	}
	if (fread(id3v1_file, 1, 128, file) != 128) {
		fprintf(stderr, "meta_id3v1_delete: fread() failed\n");
		fclose(file);
		return META_ERROR_INTERNAL;
	}

	if ((id3v1_file[0] == 'T') && (id3v1_file[1] == 'A') && (id3v1_file[2] == 'G')) {

		if (fseek(file, -128L, SEEK_END) != 0) {
			fprintf(stderr, "meta_id3v1_delete: fseek() failed\n");
			fclose(file);
			return META_ERROR_INTERNAL;
		}
	} else {

		if (fseek(file, 0L, SEEK_END) != 0) {
			fprintf(stderr, "meta_id3v1_delete: fseek() failed\n");
			fclose(file);
			return META_ERROR_INTERNAL;
		}
	}

	pos = ftell(file);
	fclose(file);

	if (truncate(filename, pos) < 0) {
		fprintf(stderr, "meta_ape_rewrite: truncate() failed on %s\n", filename);
		return META_ERROR_INTERNAL;
	}

	return META_ERROR_NONE;
}
