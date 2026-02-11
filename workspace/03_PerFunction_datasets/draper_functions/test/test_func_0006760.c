gitg_command_set_working_directory (GitgCommand *command,
                                    GFile       *working_directory)
{
	g_return_if_fail (GITG_IS_COMMAND (command));
	g_return_if_fail (working_directory == NULL || G_IS_FILE (working_directory));

	if (command->priv->working_directory)
	{
		g_object_unref (command->priv->working_directory);
		command->priv->working_directory = NULL;
	}

	if (working_directory)
	{
		command->priv->working_directory = g_file_dup (working_directory);
	}

	g_object_notify (G_OBJECT (command), "working-directory");
}
