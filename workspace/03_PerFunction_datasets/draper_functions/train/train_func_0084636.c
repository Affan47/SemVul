KTKey_free_default_action (KTKey *key)


{
	if (key->default_action.type == KTActionTypeProgram)
	{
		free (key->default_action.program.command);
	}
	else if (key->default_action.type == KTActionTypePlugin)
	{
		free (key->default_action.plugin.plugin_name);
		free (key->default_action.plugin.function_name);
	}
}
