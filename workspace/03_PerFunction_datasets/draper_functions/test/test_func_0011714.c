scg_drag_receive_spreadsheet (SheetControlGUI *scg, const gchar *uri)
{
	GError *err = NULL;
	GsfInput *input = go_file_open (uri, &err);
	GOIOContext *ioc = go_io_context_new (GO_CMD_CONTEXT (scg->wbcg));

	if (input != NULL) {
		WorkbookView *wbv;

		wbv = workbook_view_new_from_input (input, uri, NULL, ioc, NULL);
		if (wbv != NULL)
			gui_wb_view_show (scg->wbcg,
					  wbv);

	} else
		go_cmd_context_error (GO_CMD_CONTEXT (ioc), err);

	if (go_io_error_occurred (ioc) ||
	    go_io_warning_occurred (ioc)) {
		go_io_error_display (ioc);
		go_io_error_clear (ioc);
	}
	g_object_unref (ioc);
}
