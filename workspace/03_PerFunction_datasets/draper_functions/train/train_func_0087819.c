document_detect_indent_type(GeanyDocument *doc, GeanyIndentType *type_)
{
	GeanyEditor *editor = doc->editor;
	ScintillaObject *sci = editor->sci;
	gint line, line_count;
	gsize tabs = 0, spaces = 0;

	if (detect_tabs_and_spaces(editor))
	{
		*type_ = GEANY_INDENT_TYPE_BOTH;
		return TRUE;
	}

	line_count = sci_get_line_count(sci);
	for (line = 0; line < line_count; line++)
	{
		gint pos = sci_get_position_from_line(sci, line);
		gchar c;


		if (sci_get_line_indentation(sci, line) > 24)
			continue;

		c = sci_get_char_at(sci, pos);
		if (c == '\t')
			tabs++;

		else if (c == ' ' && sci_get_char_at(sci, pos + 1) == ' ')
			spaces++;
	}
	if (spaces == 0 && tabs == 0)
		return FALSE;


	if (spaces > tabs * 4)
		*type_ = GEANY_INDENT_TYPE_SPACES;
	else if (tabs > spaces * 4)
		*type_ = GEANY_INDENT_TYPE_TABS;
	else
		*type_ = GEANY_INDENT_TYPE_BOTH;

	return TRUE;
}
