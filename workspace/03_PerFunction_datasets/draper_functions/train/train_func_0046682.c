setup_man_path(void)
{
	struct strbuf new_path;
	const char *old_path = getenv("MANPATH");

	strbuf_init(&new_path, 0);


	strbuf_addstr(&new_path, GIT_MAN_PATH);
	strbuf_addch(&new_path, ':');
	if (old_path)
		strbuf_addstr(&new_path, old_path);

	setenv("MANPATH", new_path.buf, 1);

	strbuf_release(&new_path);
}
