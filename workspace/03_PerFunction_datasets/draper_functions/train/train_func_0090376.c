index_stream(unsigned char *sha1, int fd, size_t size,
			enum object_type type, const char *path,
			unsigned flags)
{
	struct child_process fast_import;
	char export_marks[512];
	const char *argv[] = { "fast-import", "--quiet", export_marks, NULL };
	char tmpfile[512];
	char fast_import_cmd[512];
	char buf[512];
	int len, tmpfd;

	strcpy(tmpfile, git_path("hashstream_XXXXXX"));
	tmpfd = git_mkstemp_mode(tmpfile, 0600);
	if (tmpfd < 0)
		die_errno("cannot create tempfile: %s", tmpfile);
	if (close(tmpfd))
		die_errno("cannot close tempfile: %s", tmpfile);
	sprintf(export_marks, "--export-marks=%s", tmpfile);

	memset(&fast_import, 0, sizeof(fast_import));
	fast_import.in = -1;
	fast_import.argv = argv;
	fast_import.git_cmd = 1;
	if (start_command(&fast_import))
		die_errno("index-stream: git fast-import failed");

	len = sprintf(fast_import_cmd, "blob\nmark :1\ndata %lu\n",
		      (unsigned long) size);
	write_or_whine(fast_import.in, fast_import_cmd, len,
		       "index-stream: feeding fast-import");
	while (size) {
		char buf[10240];
		size_t sz = size < sizeof(buf) ? size : sizeof(buf);
		size_t actual;

		actual = read_in_full(fd, buf, sz);
		if (actual < 0)
			die_errno("index-stream: reading input");
		if (write_in_full(fast_import.in, buf, actual) != actual)
			die_errno("index-stream: feeding fast-import");
		size -= actual;
	}
	if (close(fast_import.in))
		die_errno("index-stream: closing fast-import");
	if (finish_command(&fast_import))
		die_errno("index-stream: finishing fast-import");

	tmpfd = open(tmpfile, O_RDONLY);
	if (tmpfd < 0)
		die_errno("index-stream: cannot open fast-import mark");
	len = read(tmpfd, buf, sizeof(buf));
	if (len < 0)
		die_errno("index-stream: reading fast-import mark");
	if (close(tmpfd) < 0)
		die_errno("index-stream: closing fast-import mark");
	if (unlink(tmpfile))
		die_errno("index-stream: unlinking fast-import mark");
	if (len != 44 ||
	    memcmp(":1 ", buf, 3) ||
	    get_sha1_hex(buf + 3, sha1))
		die_errno("index-stream: unexpected fast-import mark: <%s>", buf);
	return 0;
}
