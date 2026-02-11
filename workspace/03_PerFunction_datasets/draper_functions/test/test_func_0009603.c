RemoveClient (Object *client)
{
	set <Object*>::iterator iter = m_Clients.find (client);
	if (iter != m_Clients.end ())
		m_Clients.erase (iter);
	if (m_ThemeType == FILE_THEME_TYPE && m_Clients.size () == 0) {
		TheThemeManager.RemoveFileTheme (this);
		if (!locked)
			delete this;
	}
}
