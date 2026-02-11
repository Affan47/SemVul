find_document_usage(GeanyDocument *doc, const gchar *search_text, gint flags)
{
	gchar *buffer, *short_file_name;
	struct Sci_TextToFind ttf;
	gint count = 0;
	gint prev_line = -1;

	g_return_val_if_fail(doc != NULL, 0);

	short_file_name = g_path_get_basename(DOC_FILENAME(doc));

	ttf.chrg.cpMin = 0;
	ttf.chrg.cpMax = sci_get_length(doc->editor->sci);
	ttf.lpstrText = (gchar *)search_text;
	while (1)
	{
		gint pos, line;

		pos = search_find_text(doc->editor->sci, flags, &ttf);
		if (pos == -1)
			break;

		count++;
		line = sci_get_line_from_position(doc->editor->sci, pos);
		if (line != prev_line)
		{
			buffer = sci_get_line(doc->editor->sci, line);
			msgwin_msg_add(COLOR_BLACK, line + 1, doc,
				"%s:%d: %s", short_file_name, line + 1, g_strstrip(buffer));
			g_free(buffer);
			prev_line = line;
		}

		ttf.chrg.cpMin = ttf.chrgText.cpMax;


		if ((ttf.chrgText.cpMax - ttf.chrgText.cpMin) == 0)
			ttf.chrg.cpMin ++;
	}
	g_free(short_file_name);
	return count;
}
