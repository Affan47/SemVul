_e2_option_file_write_unknowns (gpointer key, gpointer value, E2_FILE *f)
{
	if (e2_fs_file_write (f, "%s\n", (gchar *)value) == 0)
		write_error = TRUE;
}
