ilinemode_get (IAnjutaEditorLineMode* te, GError** err)
{
	glong eolmode;
	IAnjutaEditorLineModeType retmode;

	g_return_val_if_fail (IS_TEXT_EDITOR (te), IANJUTA_EDITOR_LINE_MODE_LF);

	eolmode = scintilla_send_message (SCINTILLA (TEXT_EDITOR (te)->scintilla),
									  SCI_GETEOLMODE, 0, 0);

	switch (eolmode) {
		case SC_EOL_CR:
			retmode = IANJUTA_EDITOR_LINE_MODE_CR;
		break;
		case SC_EOL_CRLF:
			retmode = IANJUTA_EDITOR_LINE_MODE_CRLF;
		break;
		case SC_EOL_LF:
			retmode = IANJUTA_EDITOR_LINE_MODE_LF;
		break;
		default:
			retmode = IANJUTA_EDITOR_LINE_MODE_LF;
			g_warning ("Should not be here");
	}
	return retmode;
}
