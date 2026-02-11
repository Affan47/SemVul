setPassword(bool vl)
{
	if (!entry)
		return;

	gtk_entry_set_visibility(GTK_ENTRY(entry),!vl);
	if (vl)
		gtk_entry_set_invisible_char(GTK_ENTRY(entry), (gunichar)0x25CF);
}
