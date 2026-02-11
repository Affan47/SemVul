print_metadata(FILE *fp)
{
	char uuid_str[BABELTRACE_UUID_STR_LEN];
	unsigned int major = 0, minor = 0;
	int ret;

	ret = sscanf(VERSION, "%u.%u", &major, &minor);
	if (ret != 2)
		fprintf(stderr, "[warning] Incorrect babeltrace version format\n.");
	babeltrace_uuid_unparse(s_uuid, uuid_str);
	fprintf(fp, metadata_fmt,
		major,
		minor,
		uuid_str,
		BYTE_ORDER == LITTLE_ENDIAN ? "le" : "be",
		s_timestamp ? metadata_stream_event_header_timestamp : "");
}
