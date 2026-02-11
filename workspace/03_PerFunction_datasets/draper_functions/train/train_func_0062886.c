editor_highlight_braces(GeanyEditor *editor, gint cur_pos)
{
	gint brace_pos = cur_pos - 1;

	SSM(editor->sci, SCI_SETHIGHLIGHTGUIDE, 0, 0);
	SSM(editor->sci, SCI_BRACEBADLIGHT, (uptr_t)-1, 0);

	if (! utils_isbrace(sci_get_char_at(editor->sci, brace_pos), editor_prefs.brace_match_ltgt))
	{
		brace_pos++;
		if (! utils_isbrace(sci_get_char_at(editor->sci, brace_pos), editor_prefs.brace_match_ltgt))
		{
			return;
		}
	}
	if (!brace_timeout_active)
	{
		brace_timeout_active = TRUE;

		g_timeout_add(100, delay_match_brace, GINT_TO_POINTER(brace_pos));
	}
}
