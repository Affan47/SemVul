setShowRevisions(bool bShow)
{
	if(m_bShowRevisions != bShow)
	{
		m_bShowRevisions = bShow;


		m_pDoc->setShowRevisions(bShow);


		m_pLayout->rebuildFromHere(static_cast<fl_DocSectionLayout *>(m_pLayout->getFirstSection()));


		draw(NULL);

		_fixInsertionPointCoords();
	}
}
