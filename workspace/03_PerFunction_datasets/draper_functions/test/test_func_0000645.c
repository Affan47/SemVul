help_open(struct view *view)
{
	char buf[BUFSIZ];
	int lines = ARRAY_SIZE(req_info) + 2;
	int i;

	if (view->lines > 0)
		return TRUE;

	for (i = 0; i < ARRAY_SIZE(req_info); i++)
		if (!req_info[i].request)
			lines++;

	lines += run_requests + 1;

	view->line = calloc(lines, sizeof(*view->line));
	if (!view->line)
		return FALSE;

	add_line_text(view, "Quick reference for tig keybindings:", LINE_DEFAULT);

	for (i = 0; i < ARRAY_SIZE(req_info); i++) {
		char *key;

		if (req_info[i].request == REQ_NONE)
			continue;

		if (!req_info[i].request) {
			add_line_text(view, "", LINE_DEFAULT);
			add_line_text(view, req_info[i].help, LINE_DEFAULT);
			continue;
		}

		key = get_key(req_info[i].request);
		if (!*key)
			key = "(no key defined)";

		if (!string_format(buf, "    %-25s %s", key, req_info[i].help))
			continue;

		add_line_text(view, buf, LINE_DEFAULT);
	}

	if (run_requests) {
		add_line_text(view, "", LINE_DEFAULT);
		add_line_text(view, "External commands:", LINE_DEFAULT);
	}

	for (i = 0; i < run_requests; i++) {
		struct run_request *req = get_run_request(REQ_NONE + i + 1);
		char *key;

		if (!req)
			continue;

		key = get_key_name(req->key);
		if (!*key)
			key = "(no key defined)";

		if (!string_format(buf, "    %-10s %-14s `%s`",
				   keymap_table[req->keymap].name,
				   key, req->cmd))
			continue;

		add_line_text(view, buf, LINE_DEFAULT);
	}

	return TRUE;
}
