_gda_report_document_run_converter_path (GdaReportDocument *doc, const gchar *filename,
					const gchar *full_converter_path, const gchar *converter_name,
					GError **error)
{
	gchar **argv;
	gboolean retval;

	argv = g_new (gchar *, 3);
	argv[0] = g_strdup (full_converter_path);
	argv[1] = NULL;
	argv[2] = NULL;

	retval = _gda_report_document_run_converter_argv (doc, filename, argv, 1,
							 converter_name, error);
	g_strfreev (argv);
	return retval;
}
