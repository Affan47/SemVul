fmt_dialog_selection_type (SheetView *sv,
			   GnmRange const *range,
			   gpointer user_data)
{
	FormatState *state = user_data;
	GSList *merged = gnm_sheet_merge_get_overlap (sv->sheet, range);
	GnmRange r = *range;
	gboolean allow_multi =
		merged == NULL ||
		merged->next != NULL ||
		!range_equal ((GnmRange *)merged->data, range);
	g_slist_free (merged);


	if (r.start.col != r.end.col)
	{
		if (allow_multi)
			state->selection_mask |= 2;
		else
			r.end.col = r.start.col;
	}
	if (range->start.row != range->end.row)
	{
		if (allow_multi)
			state->selection_mask |= 1;
		else
			r.end.row = r.start.row;
	}

	state->conflicts = sheet_style_find_conflicts (state->sheet, &r,
		&(state->style), state->borders);

	if ((state->conflicts & MSTYLE_FORMAT) == 0 &&
	    go_format_is_general (gnm_style_get_format (state->style))) {
		sheet_foreach_cell_in_range (state->sheet, CELL_ITER_IGNORE_BLANK,
					     r.start.col, r.start.row,
					     r.end.col,	  r.end.row,
					     cb_check_cell_format,
					     state);
	}

	return TRUE;
}
