new_filename(pb_file *pbf, ub4 len) {
	char *filename;

	if(!(filename = (char *) malloc(len + 1))) {
		fprintf(stderr, "Malloc failed of filename\n");
		fprintf(stderr, "Error: %s\n", strerror(errno));
	}
    pb_read(pbf, filename, len);
    filename[len] = '\0';

#ifdef DEBUG
    printf("filename is %s\n", filename);
#endif

	return filename;
}
