backtrace_dump(char *label, FILE *file, bool detailed)
{
	backtrace_t *backtrace;

	backtrace = backtrace_create(2);

	if (label)
	{
		println(file, "Debug backtrace: %s", label);
	}
	backtrace->log(backtrace, file, detailed);
	backtrace->destroy(backtrace);
}
