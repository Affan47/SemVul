search_mark_all(GeanyDocument *doc, const gchar *search_text, gint flags)
{
	gint pos, count = 0;
	gsize len;
	struct Sci_TextToFind ttf;

	g_return_val_if_fail(doc != NULL, 0);


	editor_indicator_clear(doc->editor, GEANY_INDICATOR_SEARCH);

	if (G_UNLIKELY(! NZV(search_text)))
		return 0;

	ttf.chrg.cpMin = 0;
	ttf.chrg.cpMax = sci_get_length(doc->editor->sci);
	ttf.lpstrText = (gchar *)search_text;
	while (TRUE)
	{
		pos = search_find_text(doc->editor->sci, flags, &ttf);
		if (pos == -1) break;

		len = ttf.chrgText.cpMax - ttf.chrgText.cpMin;
		if (len)
			editor_indicator_set_on_range(doc->editor, GEANY_INDICATOR_SEARCH, pos, pos + len);

		ttf.chrg.cpMin = ttf.chrgText.cpMax;

		if (len == 0)
			ttf.chrg.cpMin ++;
		count++;
	}
	return count;
}
