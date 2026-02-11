svn_revert_command_run (AnjutaCommand *command)
{
	SvnRevertCommand *self;
	SvnCommand *svn_command;
	GList *current_path;
	apr_array_header_t *revert_paths;
	svn_error_t *error;

	self = SVN_REVERT_COMMAND (command);
	svn_command = SVN_COMMAND (command);
	current_path = self->priv->paths;
	revert_paths = apr_array_make (svn_command_get_pool (svn_command),
								   g_list_length (self->priv->paths),
								   sizeof (char *));

	while (current_path)
	{

		(*((const char **) apr_array_push (revert_paths))) = current_path->data;
		current_path = g_list_next (current_path);
	}

	error = svn_client_revert (revert_paths,
							   self->priv->recursive,
							   svn_command_get_client_context (svn_command),
							   svn_command_get_pool (svn_command));

	if (error)
	{
		svn_command_set_error (svn_command, error);
		return 1;
	}

	return 0;
}
