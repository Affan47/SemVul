odf_preparse_table_end (GsfXMLIn *xin, G_GNUC_UNUSED GsfXMLBlob *blob)
{
	OOParseState *state = (OOParseState *)xin->user_state;
	int rows, cols;
	char *table_name = state->object_name;
	Sheet *sheet;
	sheet_order_t *sot = g_new(sheet_order_t, 1);

	cols = state->extent_data.col + 1;
	rows = state->extent_data.row + 1;
	sot->cols = cols;
	sot->rows = rows;
	odf_sheet_suggest_size (xin, &cols, &rows);

	if (table_name != NULL) {
		sheet = workbook_sheet_by_name (state->pos.wb, table_name);
		if (NULL == sheet) {
			sheet = sheet_new (state->pos.wb, table_name, cols, rows);
			workbook_sheet_attach (state->pos.wb, sheet);
		} else {

			char *new_name, *base;

			base = g_strdup_printf (_("%s_IN_CORRUPTED_FILE"), table_name);
			new_name =  workbook_sheet_get_free_name (state->pos.wb,
								  base, FALSE, FALSE);
			g_free (base);

			oo_warning (xin, _("This file is corrupted with a "
					   "duplicate sheet name \"%s\", "
					   "now renamed to \"%s\"."),
				    table_name, new_name);
			sheet = sheet_new (state->pos.wb, new_name, cols, rows);
			workbook_sheet_attach (state->pos.wb, sheet);
			g_free (new_name);
		}
	} else {
		table_name = workbook_sheet_get_free_name (state->pos.wb,
							   _("SHEET_IN_CORRUPTED_FILE"),
							   TRUE, FALSE);
		sheet = sheet_new (state->pos.wb, table_name, cols, rows);
		workbook_sheet_attach (state->pos.wb, sheet);


		oo_warning (xin, _("This file is corrupted with an "
				   "unnamed sheet "
				   "now named \"%s\"."),
			    table_name);
	}
	g_free (table_name);
	state->object_name = NULL;


	sot->sheet = sheet;
	state->sheet_order = g_slist_prepend
		(state->sheet_order, sot);
}
