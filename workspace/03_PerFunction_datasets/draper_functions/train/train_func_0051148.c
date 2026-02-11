setup_path(void)
{
	const char *old_path = getenv("PATH");
	struct strbuf new_path = STRBUF_INIT;

	add_path(&new_path, argv_exec_path);
	add_path(&new_path, getenv(EXEC_PATH_ENVIRONMENT));
	add_path(&new_path, system_path(GIT_EXEC_PATH));
	add_path(&new_path, argv0_path);

	if (old_path)
		strbuf_addstr(&new_path, old_path);
	else
		strbuf_addstr(&new_path, "/usr/local/bin:/usr/bin:/bin");

	setenv("PATH", new_path.buf, 1);

	strbuf_release(&new_path);
}
