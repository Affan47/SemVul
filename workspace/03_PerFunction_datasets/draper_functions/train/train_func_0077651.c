gui_entry_insert_char(GUI_ENTRY_REC *entry, unichar chr)
{
        g_return_if_fail(entry != NULL);

	if (chr == 0 || chr == 13 || chr == 10)
		return;

	if (entry->utf8 && entry->pos == 0 && mk_wcwidth(chr) == 0)
		return;

        gui_entry_redraw_from(entry, entry->pos);

	entry_text_grow(entry, 1);


	g_memmove(entry->text + entry->pos + 1, entry->text + entry->pos,
		  (entry->text_len-entry->pos + 1) * sizeof(unichar));

	entry->text[entry->pos] = chr;
	entry->text_len++;
        entry->pos++;

	gui_entry_fix_cursor(entry);
	gui_entry_draw(entry);
}
