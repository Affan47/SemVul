getPangoCoverage() const
{
	if(!m_pCover)
	{
		m_pCover = pango_font_get_coverage(m_pf, m_pPLang);
		UT_return_val_if_fail(m_pCover, NULL);
	}

	return m_pCover;
}
