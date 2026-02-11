find_misspelled_cb(gpointer data, gboolean forward)
{
	GtkAspell *gtkaspell = (GtkAspell *)data;
	gboolean misspelled;
	gint pos;
	gint minpos;
	gint maxpos;
	gint direc = -1;

	minpos = 0;
	maxpos = gtkaspell->end_check_pos;

	if (forward) {
		minpos = -1;
		direc = 1;
		maxpos--;
	}

	pos = get_textview_buffer_offset(gtkaspell->gtktext);
	gtkaspell->orig_pos = pos;
	while (iswordsep(get_text_index_whar(gtkaspell, pos)) &&
	       pos > minpos && pos <= maxpos)
		pos += direc;
	while (!(misspelled = check_at(gtkaspell, pos)) &&
	       pos > minpos && pos <= maxpos) {

		while (!iswordsep(get_text_index_whar(gtkaspell, pos)) &&
		       pos > minpos && pos <= maxpos)
			pos += direc;

		while (iswordsep(get_text_index_whar(gtkaspell, pos)) &&
		       pos > minpos && pos <= maxpos)
			pos += direc;
	}

	return misspelled;
}
