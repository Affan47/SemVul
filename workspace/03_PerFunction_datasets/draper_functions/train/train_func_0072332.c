assert_rule(const char *table_name, const char *rule)
{
	char *cmd, *output, **lines;
	GError **error = NULL;
	int i;

	cmd = g_strdup_printf(IPTABLES_SAVE " -t %s", table_name);
	g_spawn_command_line_sync(cmd, &output, NULL, NULL, error);
	g_free(cmd);

	lines = g_strsplit(output, "\n", 0);
	g_free(output);

	for (i = 0; lines[i] != NULL; i++) {
		DBG("lines[%02d]: %s\n", i, lines[i]);
		if (g_strcmp0(lines[i], rule) == 0)
			break;
	}
	g_strfreev(lines);

	if (lines[i] == NULL)
		return FALSE;

	return TRUE;
}
