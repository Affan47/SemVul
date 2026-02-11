event_AddClicked ()
{
	setMergeField (gtk_entry_get_text (GTK_ENTRY(m_entry)));
	addClicked();
}
