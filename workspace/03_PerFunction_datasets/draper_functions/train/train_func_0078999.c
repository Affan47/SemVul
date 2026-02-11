on_gm_world_options_option_changed(GmOptions *options, gchar *key,
		GmWorld *world) {
	if (strcmp(key, "name") == 0) {
		gm_world_name_changed(world);
	}
}
