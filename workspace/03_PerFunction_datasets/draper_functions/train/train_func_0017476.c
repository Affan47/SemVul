check_at(GtkTextBuffer *gtktext, GtkTextIter *from_pos)
{
	GtkTextIter start, end;

	char buf[BUFSIZE] = { 0 };

	if (!get_word_from_pos(gtktext, *from_pos, buf, &start, &end)) {
		return FALSE;
	}

	if (ay_spell_check(buf)) {
		gtk_text_buffer_remove_tag(gtktext, error_tag, &start, &end);
		return FALSE;
	} else {
		gtk_text_buffer_apply_tag(gtktext, error_tag, &start, &end);
		return TRUE;
	}
}
