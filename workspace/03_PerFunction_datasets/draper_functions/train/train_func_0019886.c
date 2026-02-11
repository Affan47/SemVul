compose_get_line_break_pos(GtkTextBuffer *buffer,
					   const GtkTextIter *start,
					   GtkTextIter *break_pos,
					   gint max_col,
					   gint quote_len)
{
	GtkTextIter iter = *start, line_end = *start;
	PangoLogAttr *attrs;
	gchar *str;
	gchar *p;
	gint len;
	gint i;
	gint col = 0;
	gint pos = 0;
	gboolean can_break = FALSE;
	gboolean do_break = FALSE;
	gboolean was_white = FALSE;
	gboolean prev_dont_break = FALSE;

	gtk_text_iter_forward_to_line_end(&line_end);
	str = gtk_text_buffer_get_text(buffer, &iter, &line_end, FALSE);
	len = g_utf8_strlen(str, -1);

	if (len == 0) {
		g_free(str);
		g_warning("compose_get_line_break_pos: len = 0!\n");
		return FALSE;
	}


	attrs = g_new(PangoLogAttr, len + 1);

	pango_default_break(str, -1, NULL, attrs, len + 1);

	p = str;


	for (i = 0; *p != '\0' && i < len; i++) {
		gunichar wc;

		wc = g_utf8_get_char(p);
		if (i >= quote_len && !g_unichar_isspace(wc))
			break;
		if (g_unichar_iswide(wc))
			col += 2;
		else if (*p == '\t')
			col += 8;
		else
			col++;
		p = g_utf8_next_char(p);
	}

	for (; *p != '\0' && i < len; i++) {
		PangoLogAttr *attr = attrs + i;
		gunichar wc;
		gint uri_len;

		if (attr->is_line_break && can_break && was_white && !prev_dont_break)
			pos = i;

		was_white = attr->is_white;


		if ((uri_len = get_uri_len(p)) > 0) {
			col += uri_len;
			if (pos > 0 && col > max_col) {
				do_break = TRUE;
				break;
			}
			i += uri_len - 1;
			p += uri_len;
			can_break = TRUE;
			continue;
		}

		wc = g_utf8_get_char(p);
		if (g_unichar_iswide(wc)) {
			col += 2;
			if (prev_dont_break && can_break && attr->is_line_break)
				pos = i;
		} else if (*p == '\t')
			col += 8;
		else
			col++;
		if (pos > 0 && col > max_col) {
			do_break = TRUE;
			break;
		}

		if (*p == '-' || *p == '/')
			prev_dont_break = TRUE;
		else
			prev_dont_break = FALSE;

		p = g_utf8_next_char(p);
		can_break = TRUE;
	}


	g_free(attrs);
	g_free(str);

	*break_pos = *start;
	gtk_text_iter_set_line_offset(break_pos, pos);

	return do_break;
}
