print_sgml_explanation (FILE *f, const gchar *explanation_file)
{
	gchar *raw_content;
	gsize length;

	if (explanation_file && g_file_test (explanation_file, G_FILE_TEST_EXISTS)) {
		if (!g_file_get_contents (explanation_file, &raw_content, &length, NULL)) {
			g_error ("Unable to load '%s'", explanation_file );
		}
		g_fprintf (f, "%s", raw_content);
	}
}
