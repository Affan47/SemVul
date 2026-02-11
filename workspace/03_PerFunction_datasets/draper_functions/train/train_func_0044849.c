itext_editor_insert (IAnjutaEditor *editor, IAnjutaIterable *position,
					 const gchar *txt, gint length, GError **e)
{
	gchar *text_to_insert;
	int pos;

	pos = text_editor_cell_get_position (TEXT_EDITOR_CELL (position));
	if (length < 0) length = strlen (txt);

	text_to_insert = g_strndup (txt, length);

	aneditor_command (TEXT_EDITOR(editor)->editor_id, ANE_INSERTTEXT,
		pos, (long)text_to_insert);

	g_free (text_to_insert);
}
