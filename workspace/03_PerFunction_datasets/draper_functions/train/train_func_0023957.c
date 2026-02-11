cb_show_all (GnmColRowIter const *iter, Sheet *sheet)
{
	if (iter->cri->in_advanced_filter) {
		ColRowInfo *ri = sheet_row_fetch (sheet, iter->pos);
		if (!iter->cri->visible)
			colrow_set_visibility (sheet, FALSE, TRUE,
					       iter->pos, iter->pos);
		ri->in_advanced_filter = FALSE;
	}
	return FALSE;
}
