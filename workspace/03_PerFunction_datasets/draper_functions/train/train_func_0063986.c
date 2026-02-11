updateRevisionMode()
{
	if(m_pDoc->isAutoRevisioning())
	{


		m_iViewRevision = m_pDoc->getShowRevisionId();
		m_bShowRevisions = m_pDoc->isShowRevisions();
	}


	_fixInsertionPointAfterRevision();
}
