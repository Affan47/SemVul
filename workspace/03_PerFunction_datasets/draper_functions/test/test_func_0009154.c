handle_cache(const char *path, unsigned char *sha1, const char *output)
{
	mmfile_t mmfile[3];
	mmbuffer_t result = {NULL, 0};
	struct cache_entry *ce;
	int pos, len, i, hunk_no;
	struct rerere_io_mem io;
	int marker_size = ll_merge_marker_size(path);


	len = strlen(path);
	pos = cache_name_pos(path, len);
	if (0 <= pos)
		return -1;
	pos = -pos - 1;

	for (i = 0; i < 3; i++) {
		enum object_type type;
		unsigned long size;

		mmfile[i].size = 0;
		mmfile[i].ptr = NULL;
		if (active_nr <= pos)
			break;
		ce = active_cache[pos++];
		if (ce_namelen(ce) != len || memcmp(ce->name, path, len)
		    || ce_stage(ce) != i + 1)
			break;
		mmfile[i].ptr = read_sha1_file(ce->sha1, &type, &size);
		mmfile[i].size = size;
	}
	for (i = 0; i < 3; i++) {
		if (!mmfile[i].ptr && !mmfile[i].size)
			mmfile[i].ptr = xstrdup("");
	}
	ll_merge(&result, path, &mmfile[0],
		 &mmfile[1], "ours",
		 &mmfile[2], "theirs", 0);
	for (i = 0; i < 3; i++)
		free(mmfile[i].ptr);

	memset(&io, 0, sizeof(io));
	io.io.getline = rerere_mem_getline;
	if (output)
		io.io.output = fopen(output, "w");
	else
		io.io.output = NULL;
	strbuf_init(&io.input, 0);
	strbuf_attach(&io.input, result.ptr, result.size, result.size);

	hunk_no = handle_path(sha1, (struct rerere_io *)&io, marker_size);
	strbuf_release(&io.input);
	if (io.io.output)
		fclose(io.io.output);
	return hunk_no;
}
