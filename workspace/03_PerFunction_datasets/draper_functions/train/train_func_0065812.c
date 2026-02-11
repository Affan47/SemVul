pending_command_complete(char *message)
{
	__connmanctl_save_rl();

	fprintf(stdout, "%s", message);

	__connmanctl_redraw_rl();

	if (__connmanctl_is_interactive() == true)
		__connmanctl_command_mode();
	else
		__connmanctl_agent_mode("", NULL);
}
