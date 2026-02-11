OnNameActivate ()
{
	char const *text = gtk_entry_get_text (m_NameEntry);
	m_ValidName = strlen (text) > 0;
	gtk_widget_set_sensitive (m_SaveBtn, m_ValidName && m_ValidSymbols);
}
