SetLocale(const wxString& language)
{
	if (!language.IsEmpty()) {
		m_language = language;
		if (m_locale) {
			delete m_locale;
		}
		m_locale = new wxLocale;
		InitLocale(*m_locale, StrLang2wx(language));
	}

	return m_locale == NULL ? wxString() : m_locale->GetCanonicalName();
}
