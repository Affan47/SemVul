rb_gst_get_default_encoding_target ()
{
	if (default_target == NULL) {
		char *target_file;
		GError *error = NULL;

		target_file = get_encoding_target_file ();
		default_target = gst_encoding_target_load_from_file (target_file, &error);
		if (default_target == NULL) {
			g_warning ("Unable to load encoding profiles from %s: %s", target_file, error ? error->message : "no error");
			g_clear_error (&error);
			g_free (target_file);
			return NULL;
		}
		g_free (target_file);
	}

	return default_target;
}
