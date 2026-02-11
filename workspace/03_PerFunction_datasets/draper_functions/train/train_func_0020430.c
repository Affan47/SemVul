git_rebase_continue_command_run (AnjutaCommand *command)
{
	GitRebaseContinueCommand *self;

	self = GIT_REBASE_CONTINUE_COMMAND (command);

	git_command_add_arg (GIT_COMMAND (command), "rebase");

	switch (self->priv->action)
	{
		case GIT_REBASE_CONTINUE_ACTION_CONTINUE:
			git_command_add_arg (GIT_COMMAND (command), "--continue");
			break;
		case GIT_REBASE_CONTINUE_ACTION_SKIP:
			git_command_add_arg (GIT_COMMAND (command), "--skip");
			break;
		case GIT_REBASE_CONTINUE_ACTION_ABORT:
			git_command_add_arg (GIT_COMMAND (command), "--abort");
			break;
		default:
			break;
	}

	return 0;
}
