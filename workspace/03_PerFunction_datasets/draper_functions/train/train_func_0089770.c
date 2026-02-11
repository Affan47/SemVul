stf_read_workbook (G_GNUC_UNUSED GOFileOpener const *fo,  gchar const *enc,
		   GOIOContext *context, GoView *view, GsfInput *input)
{
	DialogStfResult_t *dialogresult = NULL;
	char *name, *nameutf8 = NULL;
	char *data = NULL;
	size_t data_len;
	WorkbookView *wbv = WORKBOOK_VIEW (view);

	if (!IS_WBC_GTK (context->impl)) {
		go_io_error_string (context, _("This importer can only be used with a GUI."));
		return;
	}

	name = g_path_get_basename (gsf_input_name (input));
	nameutf8 = g_filename_to_utf8 (name, -1, NULL, NULL, NULL);
	g_free (name);
	if (!nameutf8) {
		g_warning ("Failed to convert filename to UTF-8.  This shouldn't happen here.");
		goto out;
	}

	data = stf_preparse (context, input, &data_len);
	if (!data)
		goto out;

	dialogresult = stf_dialog (WBC_GTK (context->impl),
				   enc, FALSE, NULL, FALSE,
				   nameutf8, data, data_len);
	if (dialogresult != NULL) {
		Workbook *book = wb_view_get_workbook (wbv);
		int cols = dialogresult->colcount, rows = dialogresult->rowcount;
		Sheet *sheet;

		gnm_sheet_suggest_size (&cols, &rows);
		sheet = sheet_new (book, nameutf8, cols, rows);
		workbook_sheet_attach (book, sheet);
		if (stf_store_results (dialogresult, sheet, 0, 0)) {
			workbook_recalc_all (book);
			resize_columns (sheet);
			workbook_set_saveinfo
				(book,
				 GO_FILE_FL_WRITE_ONLY,
				 go_file_saver_for_id
				 ("Gnumeric_stf:stf_assistant"));
		} else {


			workbook_sheet_delete (sheet);
		}
	}

 out:
	g_free (nameutf8);
	g_free (data);
	if (dialogresult != NULL)
		stf_dialog_result_free (dialogresult);
}
