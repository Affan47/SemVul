next_word (CellEdit *edit,
           gint start)
{
	gchar *p;
	gint length;

	length = strlen (edit->text);
	if (start >= length)
		return length;

	p = g_utf8_next_char (edit->text + start);

	while (*p && g_unichar_validate (g_utf8_get_char (p))) {
		gunichar unival = g_utf8_get_char (p);
		if (g_unichar_isspace (unival))
			return p - edit->text;
		p = g_utf8_next_char (p);
	}

	return p - edit->text;
}
