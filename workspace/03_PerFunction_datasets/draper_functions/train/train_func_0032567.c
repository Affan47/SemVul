dif_file_open (GOFileOpener const *fo, GOIOContext *io_context,
               WorkbookView *wbv, GsfInput *input)
{
	Workbook *wb = wb_view_get_workbook (wbv);
	DifInputContext *ctxt = dif_input_context_new (io_context, wb, input);

	workbook_set_saveinfo (wb, GO_FILE_FL_MANUAL_REMEMBER,
		go_file_saver_for_id ("Gnumeric_dif:dif"));
	if (ctxt != NULL) {
		dif_parse_sheet (ctxt);
		if (go_io_error_occurred (io_context))
			go_io_error_push (io_context,
				go_error_info_new_str (_("Error while reading DIF file.")));
		dif_input_context_destroy (ctxt);
	} else if (!go_io_error_occurred (io_context))
		go_io_error_unknown (io_context);
}
