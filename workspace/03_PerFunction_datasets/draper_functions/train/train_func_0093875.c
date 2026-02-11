OkFindEntryDialog(GtkWidget * widget, gpointer data)
{
	if (GTK_TOGGLE_BUTTON(((FindEntryData *) data)->nameB)->active)
		findEntryStruct.type = FIND_NAME;
	else
		findEntryStruct.type = FIND_NUMBER;

	strncpy(findEntryStruct.pattern,
		gtk_entry_get_text(GTK_ENTRY(((FindEntryData *) data)->pattern)),
		max_phonebook_number_length);
	findEntryStruct.pattern[max_phonebook_number_length] = '\0';

	findEntryStruct.lastRow = 0;

	gtk_widget_hide(((FindEntryData *) data)->dialog);

	SearchEntry();
}
