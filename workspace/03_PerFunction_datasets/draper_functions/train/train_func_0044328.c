find_offset_into_line (EText *text,
                       gint offset_into_text,
                       gchar **start_of_line)
{
	gchar *p;

	p = g_utf8_offset_to_pointer (text->text, offset_into_text);

	if (p == text->text) {
		if (start_of_line)
			*start_of_line = (gchar *)text->text;
		return 0;
	}
	else {
		p = g_utf8_find_prev_char (text->text, p);

		while (p && p > text->text) {
			if (*p == '\n') {
				if (start_of_line)
					*start_of_line = p+1;
				return offset_into_text -
					g_utf8_pointer_to_offset (
					text->text, p + 1);
			}
			p = g_utf8_find_prev_char (text->text, p);
		}

		if (start_of_line)
			*start_of_line = (gchar *)text->text;
		return offset_into_text;
	}
}
