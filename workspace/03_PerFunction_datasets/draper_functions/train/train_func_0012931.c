gm_world_input_view_str_new_value(gchar *old, gchar *new) {
	g_free(old);

	if (new) {
		return g_strdup(new);
	} else {
		return NULL;
	}
}
