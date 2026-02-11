gui_entry_move_words_left(GUI_ENTRY_REC *entry, int count, int to_space)
{
	int pos;

	pos = entry->pos;
	while (count > 0 && pos > 0) {
		if (to_space) {
			while (pos > 0 && entry->text[pos-1] == ' ')
				pos--;
			while (pos > 0 && entry->text[pos-1] != ' ')
				pos--;
		} else {
			while (pos > 0 && !i_isalnum(entry->text[pos-1]))
				pos--;
			while (pos > 0 &&  i_isalnum(entry->text[pos-1]))
				pos--;
		}
		count--;
	}

        entry->pos = pos;
}
