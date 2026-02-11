svn_switch_command_run (AnjutaCommand *command)
{
	SvnSwitchCommand *self;
	SvnCommand *svn_command;
	svn_opt_revision_t revision;
	svn_revnum_t switched_revision;
	gchar *revision_message;
	svn_error_t *error;

	self = SVN_SWITCH_COMMAND (command);
	svn_command = SVN_COMMAND (command);

	if (self->priv->revision == SVN_SWITCH_REVISION_HEAD)
		revision.kind = svn_opt_revision_head;
	else
	{
		revision.kind = svn_opt_revision_number;
		revision.value.number = self->priv->revision;
	}

	error = svn_client_switch (&switched_revision,
							   self->priv->working_copy_path,
							   self->priv->branch_url,
							   &revision,
							   self->priv->recursive,
							   svn_command_get_client_context (svn_command),
							   svn_command_get_pool (svn_command));

	if (error)
	{
		svn_command_set_error (svn_command, error);
		return 1;
	}

	revision_message = g_strdup_printf ("Switched to revision %ld.",
										switched_revision);

	svn_command_push_info (svn_command, revision_message);
	g_free (revision_message);

	return 0;
}
