list_commands(void)
{
	unsigned int longest = load_command_list();
	const char *exec_path = git_exec_path();

	if (main_cmds.cnt) {
		printf("available git commands in '%s'\n", exec_path);
		printf("----------------------------");
		mput_char('-', strlen(exec_path));
		putchar('\n');
		pretty_print_string_list(&main_cmds, longest);
		putchar('\n');
	}

	if (other_cmds.cnt) {
		printf("git commands available from elsewhere on your $PATH\n");
		printf("---------------------------------------------------\n");
		pretty_print_string_list(&other_cmds, longest);
		putchar('\n');
	}
}
