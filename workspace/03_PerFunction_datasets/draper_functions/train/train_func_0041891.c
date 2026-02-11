multitext_free(struct multitext_widget *mt)
{
	int i;

	gtk_entry_set_text(GTK_ENTRY(mt->entry), "");

	for (i = 0; i < mt->max_text; i++) {
		if (mt->text[i])
			free(mt->text[i]);
	}

	free(mt->text);
	mt->cur_text = -1;
	mt->max_text = 0;
}
