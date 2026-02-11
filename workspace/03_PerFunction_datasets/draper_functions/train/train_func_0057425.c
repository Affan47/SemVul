totem_embedded_do_command (TotemEmbedded *embedded,
			   const char *command,
			   GError **error)
{
	g_return_val_if_fail (command != NULL, FALSE);

	g_message ("totem_embedded_do_command: %s", command);

	if (strcmp (command, TOTEM_COMMAND_PLAY) == 0) {
		return totem_embedded_play (embedded, error);
	}
	if (strcmp (command, TOTEM_COMMAND_PAUSE) == 0) {
		return totem_embedded_pause (embedded, error);
	}
	if (strcmp (command, TOTEM_COMMAND_STOP) == 0) {
		return totem_embedded_stop (embedded, error);
	}

	g_set_error (error,
                     TOTEM_EMBEDDED_ERROR_QUARK,
                     TOTEM_EMBEDDED_UNKNOWN_COMMAND,
                     "Unknown command '%s'", command);
	return FALSE;
}
