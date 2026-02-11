interface_save_accels (void)
{
	gchar *accel_map_filename = g_build_filename (g_get_home_dir(), GERBV_ACCELS_RELPATH, NULL);
	if (accel_map_filename) {
		gtk_accel_map_save (accel_map_filename);
		g_free (accel_map_filename);
	}
}
