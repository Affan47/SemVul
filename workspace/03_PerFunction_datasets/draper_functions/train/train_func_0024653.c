run_hook(const char *hook_name)
{
	static char buf[sizeof(commands->old_sha1) * 2 + PATH_MAX + 4];
	struct command *cmd;
	struct child_process proc;
	const char *argv[2];
	int have_input = 0, code;

	for (cmd = commands; !have_input && cmd; cmd = cmd->next) {
		if (!cmd->error_string)
			have_input = 1;
	}

	if (!have_input || access(hook_name, X_OK) < 0)
		return 0;

	argv[0] = hook_name;
	argv[1] = NULL;

	memset(&proc, 0, sizeof(proc));
	proc.argv = argv;
	proc.in = -1;
	proc.stdout_to_stderr = 1;

	code = start_command(&proc);
	if (code)
		return hook_status(code, hook_name);
	for (cmd = commands; cmd; cmd = cmd->next) {
		if (!cmd->error_string) {
			size_t n = snprintf(buf, sizeof(buf), "%s %s %s\n",
				sha1_to_hex(cmd->old_sha1),
				sha1_to_hex(cmd->new_sha1),
				cmd->ref_name);
			if (write_in_full(proc.in, buf, n) != n)
				break;
		}
	}
	close(proc.in);
	return hook_status(finish_command(&proc), hook_name);
}
