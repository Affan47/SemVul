workbook_sheet_move (Sheet *sheet, int direction)
{
	Workbook *wb;
	gint old_pos, new_pos;

	g_return_if_fail (IS_SHEET (sheet));

	wb = sheet->workbook;

	pre_sheet_index_change (wb);
        old_pos = sheet->index_in_wb;
	new_pos = old_pos + direction;

	if (0 <= new_pos && new_pos < workbook_sheet_count (wb)) {
		int min_pos = MIN (old_pos, new_pos);
		int max_pos = MAX (old_pos, new_pos);

		g_ptr_array_remove_index (wb->sheets, old_pos);
		go_ptr_array_insert (wb->sheets, sheet, new_pos);

		for (; max_pos >= min_pos ; max_pos--) {
			Sheet *sheet = g_ptr_array_index (wb->sheets, max_pos);
			sheet->index_in_wb = max_pos;
		}
	}

	post_sheet_index_change (wb);

	go_doc_set_dirty (GO_DOC (wb), TRUE);
}
