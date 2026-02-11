gedit_settings_get_lockdown (GeditSettings *gs)
{
	guint lockdown = 0;
	gboolean command_line, printing, print_setup, save_to_disk;

	command_line = g_settings_get_boolean (gs->priv->lockdown,
					       GEDIT_SETTINGS_LOCKDOWN_COMMAND_LINE);
	printing = g_settings_get_boolean (gs->priv->lockdown,
					   GEDIT_SETTINGS_LOCKDOWN_PRINTING);
	print_setup = g_settings_get_boolean (gs->priv->lockdown,
					      GEDIT_SETTINGS_LOCKDOWN_PRINT_SETUP);
	save_to_disk = g_settings_get_boolean (gs->priv->lockdown,
					       GEDIT_SETTINGS_LOCKDOWN_SAVE_TO_DISK);

	if (command_line)
		lockdown |= GEDIT_LOCKDOWN_COMMAND_LINE;

	if (printing)
		lockdown |= GEDIT_LOCKDOWN_PRINTING;

	if (print_setup)
		lockdown |= GEDIT_LOCKDOWN_PRINT_SETUP;

	if (save_to_disk)
		lockdown |= GEDIT_LOCKDOWN_SAVE_TO_DISK;

	return lockdown;
}
