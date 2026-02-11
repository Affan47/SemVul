read_raw_file(char *filename)
{
	struct ccd_frame *frame;
	struct raw_file raw;
	raw_read_func reader;
	struct stat statbuf;

	reader = raw_reader(filename);
	if (! reader) {
		return read_file_from_dcraw(filename);
	}

	frame = NULL;
	bzero(&raw, sizeof(raw));

	if (stat(filename, &statbuf)) {
		err_printf("read_raw_file: stat %s: %s\n", filename, strerror(errno));
		return NULL;
	}

	raw.file_len = statbuf.st_size;

	raw.filename = filename;
	raw.fd = open(filename, O_RDONLY);
	if (raw.fd == -1) {
		err_printf("read_raw_file: open %s: %s\n", filename, strerror(errno));
		return NULL;
	}

	frame = reader(&raw);
	set_color_field(frame);

	close(raw.fd);
	return frame;
}
