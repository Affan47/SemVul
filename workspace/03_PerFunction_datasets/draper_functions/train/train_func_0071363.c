read_index_info(int line_termination)
{
	struct strbuf buf;
	struct strbuf uq;

	strbuf_init(&buf, 0);
	strbuf_init(&uq, 0);
	while (strbuf_getline(&buf, stdin, line_termination) != EOF) {
		char *ptr, *tab;
		char *path_name;
		unsigned char sha1[20];
		unsigned int mode;
		unsigned long ul;
		int stage;


		errno = 0;
		ul = strtoul(buf.buf, &ptr, 8);
		if (ptr == buf.buf || *ptr != ' '
		    || errno || (unsigned int) ul != ul)
			goto bad_line;
		mode = ul;

		tab = strchr(ptr, '\t');
		if (!tab || tab - ptr < 41)
			goto bad_line;

		if (tab[-2] == ' ' && '0' <= tab[-1] && tab[-1] <= '3') {
			stage = tab[-1] - '0';
			ptr = tab + 1;
			tab = tab - 2;
		}
		else {
			stage = 0;
			ptr = tab + 1;
		}

		if (get_sha1_hex(tab - 40, sha1) || tab[-41] != ' ')
			goto bad_line;

		path_name = ptr;
		if (line_termination && path_name[0] == '"') {
			strbuf_reset(&uq);
			if (unquote_c_style(&uq, path_name, NULL)) {
				die("git update-index: bad quoting of path name");
			}
			path_name = uq.buf;
		}

		if (!verify_path(path_name)) {
			fprintf(stderr, "Ignoring path %s\n", path_name);
			continue;
		}

		if (!mode) {

			if (remove_file_from_cache(path_name))
				die("git update-index: unable to remove %s",
				    ptr);
		}
		else {


			ptr[-42] = ptr[-1] = 0;
			if (add_cacheinfo(mode, sha1, path_name, stage))
				die("git update-index: unable to update %s",
				    path_name);
		}
		continue;

	bad_line:
		die("malformed index info %s", buf.buf);
	}
	strbuf_release(&buf);
	strbuf_release(&uq);
}
