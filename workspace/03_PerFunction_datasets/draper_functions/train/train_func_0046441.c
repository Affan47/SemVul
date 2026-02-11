CreateLayout()
{
	m_topsizer = new wxBoxSizer(wxVERTICAL);
	AddEngineSizer(m_topsizer);
	AddConfigSizer(m_topsizer);
	AddSyncTypeSizer(m_topsizer);
	AddFavourSizer(m_topsizer);
	AddButtonSizer(m_topsizer);

	SetSizer(m_topsizer);
	m_topsizer->SetSizeHints(this);
	m_topsizer->Layout();
}
