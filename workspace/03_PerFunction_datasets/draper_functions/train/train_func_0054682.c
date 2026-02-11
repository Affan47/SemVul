xlsx_cellref_as_string (GnmConventionsOut *out,
			GnmCellRef const *cell_ref,
			G_GNUC_UNUSED gboolean no_sheetname)
{
	Sheet const *sheet = cell_ref->sheet;


	if (sheet != NULL) {
		xlsx_add_extern_id (out, sheet->workbook);
		g_string_append (out->accum, sheet->name_quoted);
		g_string_append_c (out->accum, '!');
	}
	cellref_as_string (out, cell_ref, TRUE);
}
