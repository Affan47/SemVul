gui_entry_get_cutbuffer(GUI_ENTRY_REC *entry)
{
	char *buf;
        int i;

	g_return_val_if_fail(entry != NULL, NULL);

	if (entry->cutbuffer == NULL)
                return NULL;

	if (entry->utf8)
		buf = g_ucs4_to_utf8(entry->cutbuffer, -1, NULL, NULL, NULL);
	else {
		buf = g_malloc(entry->cutbuffer_len*6 + 1);
		if (term_type == TERM_TYPE_BIG5)
			unichars_to_big5(entry->cutbuffer, buf);
		else
			for (i = 0; i <= entry->cutbuffer_len; i++)
				buf[i] = entry->cutbuffer[i];
	}
	return buf;
}
