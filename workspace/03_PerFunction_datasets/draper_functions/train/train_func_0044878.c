text_editor_goto_point (TextEditor * te, glong point)
{
	g_return_val_if_fail (te != NULL, FALSE);
	g_return_val_if_fail(IS_SCINTILLA (te->scintilla) == TRUE, FALSE);

	scintilla_send_message (SCINTILLA (te->scintilla), SCI_GOTOPOS, point, 0);
	return TRUE;
}
