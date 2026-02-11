OnTitleChanged (GtkEntry *entry, Document *doc)
{
	char const *txt = gtk_entry_get_text (entry);
	if (txt && *txt == 0)
		txt = NULL;
	doc->SetTitle (txt);
	doc->RenameViews ();
	doc->SetDirty ();
}
