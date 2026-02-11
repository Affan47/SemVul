NewEntry(void)
{
	PhonebookEntry *entry;

	if (contactsMemoryInitialized) {
		if ((entry = FindFreeEntry(GN_MT_ME)) != NULL) {
			memset(entry, 0, sizeof(PhonebookEntry));
			entry->entry.memory_type = GN_MT_ME;
			NewPbEntry(entry);
		} else if ((entry = FindFreeEntry(GN_MT_SM)) != NULL) {
			memset(entry, 0, sizeof(PhonebookEntry));
			entry->entry.memory_type = GN_MT_SM;
			NewPbEntry(entry);
		} else {
			gtk_label_set_text(GTK_LABEL(errorDialog.text),
					   _("Can't find free memory."));
			gtk_widget_show(errorDialog.dialog);
		}
	}
}
