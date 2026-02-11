proj_title_changed (GtkEntry *entry, NotesArea *na)
{
	PRJ_SETUP
	str = gtk_entry_get_text (entry);
	gtt_project_set_title (na->proj, str);
	na->ignore_events = FALSE;
}
