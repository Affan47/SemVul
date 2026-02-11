userlist_read(session_t *session) {
	const char *filename;
	char *buf;
	FILE *f;

	if (!(filename = prepare_pathf("%s-userlist", session->uid)))
		return -1;

	if (!(f = fopen(filename, "r")))
		return -1;

	while ((buf = read_file(f, 0))) {
		if (buf[0] == '#' || (buf[0] == '/' && buf[1] == '/'))
			continue;

		userlist_add_entry(session, buf);
	}

	query_emit_id(NULL, USERLIST_REFRESH);

	fclose(f);

	return 0;
}
