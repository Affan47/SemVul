setAlignment(int al)
{
	if (!entry)
		return;
	gtk_entry_set_alignment(GTK_ENTRY(entry), gt_from_alignment(al));
}
