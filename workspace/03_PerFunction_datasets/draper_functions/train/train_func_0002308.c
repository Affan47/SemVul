handle_alias(int *argcp, const char ***argv)
{
	int envchanged = 0, ret = 0, saved_errno = errno;
	const char *subdir;
	int count, option_count;
	const char **new_argv;
	const char *alias_command;
	char *alias_string;
	int unused_nongit;

	subdir = setup_git_directory_gently(&unused_nongit);

	alias_command = (*argv)[0];
	alias_string = alias_lookup(alias_command);
	if (alias_string) {
		if (alias_string[0] == '!') {
			commit_pager_choice();
			if (*argcp > 1) {
				struct strbuf buf;

				strbuf_init(&buf, PATH_MAX);
				strbuf_addstr(&buf, alias_string);
				sq_quote_argv(&buf, (*argv) + 1, PATH_MAX);
				free(alias_string);
				alias_string = buf.buf;
			}
			trace_printf("trace: alias to shell cmd: %s => %s\n",
				     alias_command, alias_string + 1);
			ret = system(alias_string + 1);
			if (ret >= 0 && WIFEXITED(ret) &&
			    WEXITSTATUS(ret) != 127)
				exit(WEXITSTATUS(ret));
			die("Failed to run '%s' when expanding alias '%s'",
			    alias_string + 1, alias_command);
		}
		count = split_cmdline(alias_string, &new_argv);
		if (count < 0)
			die("Bad alias.%s string: %s", alias_command,
			    split_cmdline_strerror(count));
		option_count = handle_options(&new_argv, &count, &envchanged);
		if (envchanged)
			die("alias '%s' changes environment variables\n"
				 "You can use '!git' in the alias to do this.",
				 alias_command);
		memmove(new_argv - option_count, new_argv,
				count * sizeof(char *));
		new_argv -= option_count;

		if (count < 1)
			die("empty alias for %s", alias_command);

		if (!strcmp(alias_command, new_argv[0]))
			die("recursive alias: %s", alias_command);

		trace_argv_printf(new_argv,
				  "trace: alias expansion: %s =>",
				  alias_command);

		new_argv = xrealloc(new_argv, sizeof(char *) *
				    (count + *argcp));

		memcpy(new_argv + count, *argv + 1, sizeof(char *) * *argcp);

		*argv = new_argv;
		*argcp += count - 1;

		ret = 1;
	}

	if (subdir && chdir(subdir))
		die_errno("Cannot change to '%s'", subdir);

	errno = saved_errno;

	return ret;
}
