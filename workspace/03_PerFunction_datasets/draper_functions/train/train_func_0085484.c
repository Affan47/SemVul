parse_file_format_version(const char *line)
{
	struct version v;
	uint16_t major, minor;

	if (sscanf(line, "# EVEMU %hd.%hd\n", &major, &minor) != 2) {
		major = 1;
		minor = 0;
	}


	v = version(major, minor);

	if (version_cmp(v, version(EVEMU_FILE_MAJOR, EVEMU_FILE_MINOR)) > 0)
		fprintf(stderr, "Warning: file format %d.%d is newer than "
				"supported version %d.%d.\n",
			major, minor, EVEMU_FILE_MAJOR, EVEMU_FILE_MINOR);

	return v;
}
