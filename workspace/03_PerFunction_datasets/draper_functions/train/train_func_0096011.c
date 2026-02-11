cb_exporter_finalize (Workbook *wb, GOFileSaver *saver)
{
	g_return_if_fail (GO_IS_FILE_SAVER (saver));
	g_return_if_fail (IS_WORKBOOK (wb));
	g_return_if_fail (wb->file_exporter == saver);
	workbook_set_file_exporter (wb, NULL);
}
