workbook_set_file_exporter (Workbook *wb, GOFileSaver *fs)
{
	wb->file_exporter = fs;
	WORKBOOK_FOREACH_CONTROL (wb, wbv, wbc,
				  wb_control_menu_state_update (wbc, MS_FILE_EXPORT_IMPORT););
}
