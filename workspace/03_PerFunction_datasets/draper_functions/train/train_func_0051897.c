save_state(void)
{
	int len;
	struct child_process cp;
	struct strbuf buffer = STRBUF_INIT;
	const char *argv[] = {"stash", "create", NULL};

	memset(&cp, 0, sizeof(cp));
	cp.argv = argv;
	cp.out = -1;
	cp.git_cmd = 1;

	if (start_command(&cp))
		die("could not run stash.");
	len = strbuf_read(&buffer, cp.out, 1024);
	close(cp.out);

	if (finish_command(&cp) || len < 0)
		die("stash failed");
	else if (!len)
		return;
	strbuf_setlen(&buffer, buffer.len-1);
	if (get_sha1(buffer.buf, stash))
		die("not a valid object: %s", buffer.buf);
}
