uoenc_outfile_name(char * filename) {
	if(filename == NULL) {
		fprintf(stderr, "Error: uoenc_outfile_name 'filename' was NULL\n");
		return NULL;
	}
	char extension[] = EXTENSION;
	size_t infile_name_len = strnlen(filename,
		NAME_MAX - sizeof(extension));
	size_t outfile_name_len = infile_name_len + sizeof(extension);
	char * outfile_name = malloc(outfile_name_len);
	snprintf(outfile_name, outfile_name_len, "%*s%s", (int) infile_name_len,
		filename, extension);
	return outfile_name;
}
