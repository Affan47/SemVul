run_add_interactive(const char *revision, const char *patch_mode,
			const char **pathspec)
{
	int status, ac, pc = 0;
	const char **args;

	if (pathspec)
		while (pathspec[pc])
			pc++;

	args = xcalloc(sizeof(const char *), (pc + 5));
	ac = 0;
	args[ac++] = "add--interactive";
	if (patch_mode)
		args[ac++] = patch_mode;
	if (revision)
		args[ac++] = revision;
	args[ac++] = "--";
	if (pc) {
		memcpy(&(args[ac]), pathspec, sizeof(const char *) * pc);
		ac += pc;
	}
	args[ac] = NULL;

	status = run_command_v_opt(args, RUN_GIT_CMD);
	free(args);
	return status;
}
