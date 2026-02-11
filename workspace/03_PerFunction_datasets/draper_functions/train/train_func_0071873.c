gnm_page_breaks_append_break (GnmPageBreaks *breaks,
			      int pos,
			      GnmPageBreakType type)
{
	GnmPageBreak const *prev;
	GnmPageBreak info;

	g_return_val_if_fail (breaks != NULL, FALSE);

	if (type == GNM_PAGE_BREAK_NONE)
		return TRUE;


	if (pos < 0)
		return FALSE;
	if (breaks->details->len > 0) {
		prev = &g_array_index (breaks->details, GnmPageBreak,
			breaks->details->len-1);
		if (prev->pos >= pos)
			return FALSE;
	}

	info.pos   = pos;
	info.type  = type;
	g_array_append_val (breaks->details, info);

	return TRUE;
}
