gm_world_load_input_history(GmWorld *world) {
	FILE *f;
	gchar line[1024], *filename;
	GString *str;

	filename = g_strconcat(world->priv->path, G_DIR_SEPARATOR_S, "history",
  		NULL);

	gm_debug_msg(DEBUG_DEFAULT, "GmWorld.LoadInputHistory: loading history "
			"(%s)!", filename);

	if ((f = fopen(filename, "r")) != NULL) {
		str = g_string_new("");

		while (fgets(line, 1024 - 1, f) != NULL) {
			g_string_append(str, line);
			if (line[strlen(line) - 1] == '\n') {
				if (line[1] != '\0') {

					world->priv->history = g_list_append(world->priv->history,
							g_strndup(str->str, strlen(str->str) - 1));
				}
				g_string_erase(str, 0, -1);
			}
		}

		g_string_free(str, TRUE);
		fclose(f);
	} else {
		gm_debug_msg(DEBUG_DEFAULT, "GmWorld.LoadInputHistory: could not "
				"retrieve contents of file %s (%s)", filename, strerror(errno));
	}

	g_free(filename);
}
