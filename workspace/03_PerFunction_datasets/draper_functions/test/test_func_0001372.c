read_header(const char *path, struct bundle_header *header) {
	char buffer[1024];
	int fd = open(path, O_RDONLY);

	if (fd < 0)
		return error("could not open '%s'", path);
	if (read_string(fd, buffer, sizeof(buffer)) < 0 ||
			strcmp(buffer, bundle_signature)) {
		close(fd);
		return error("'%s' does not look like a v2 bundle file", path);
	}
	while (read_string(fd, buffer, sizeof(buffer)) > 0
			&& buffer[0] != '\n') {
		int is_prereq = buffer[0] == '-';
		int offset = is_prereq ? 1 : 0;
		int len = strlen(buffer);
		unsigned char sha1[20];
		struct ref_list *list = is_prereq ? &header->prerequisites
			: &header->references;
		char delim;

		if (buffer[len - 1] == '\n')
			buffer[len - 1] = '\0';
		if (get_sha1_hex(buffer + offset, sha1)) {
			warning("unrecognized header: %s", buffer);
			continue;
		}
		delim = buffer[40 + offset];
		if (!isspace(delim) && (delim != '\0' || !is_prereq))
			die ("invalid header: %s", buffer);
		add_to_ref_list(sha1, isspace(delim) ?
				buffer + 41 + offset : "", list);
	}
	return fd;
}
