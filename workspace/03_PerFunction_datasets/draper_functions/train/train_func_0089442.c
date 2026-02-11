delay_match_brace(G_GNUC_UNUSED gpointer user_data)
{
	GeanyDocument *doc = document_get_current();
	GeanyEditor *editor;
	gint brace_pos = GPOINTER_TO_INT(user_data);
	gint end_pos, cur_pos;

	brace_timeout_active = FALSE;
	if (!doc)
		return FALSE;

	editor = doc->editor;
	cur_pos = sci_get_current_position(editor->sci) - 1;

	if (cur_pos != brace_pos)
	{
		cur_pos++;
		if (cur_pos != brace_pos)
		{


			editor_highlight_braces(editor, cur_pos);
			return FALSE;
		}
	}
	if (!utils_isbrace(sci_get_char_at(editor->sci, brace_pos), editor_prefs.brace_match_ltgt))
	{
		editor_highlight_braces(editor, cur_pos);
		return FALSE;
	}
	end_pos = sci_find_matching_brace(editor->sci, brace_pos);

	if (end_pos >= 0)
	{
		gint col = MIN(sci_get_col_from_position(editor->sci, brace_pos),
			sci_get_col_from_position(editor->sci, end_pos));
		SSM(editor->sci, SCI_SETHIGHLIGHTGUIDE, col, 0);
		SSM(editor->sci, SCI_BRACEHIGHLIGHT, brace_pos, end_pos);
	}
	else
	{
		SSM(editor->sci, SCI_SETHIGHLIGHTGUIDE, 0, 0);
		SSM(editor->sci, SCI_BRACEBADLIGHT, brace_pos, 0);
	}
	return FALSE;
}
