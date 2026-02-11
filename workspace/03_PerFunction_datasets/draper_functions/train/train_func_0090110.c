ThreadRebuildLists()
{


	if ( m_pSearchIndex->RebuildLists() == 0 )
	{
		m_pSearchIndex->SaveIndex();
		m_pFileManagerInfo->m_eFileManagerStatus = efmsNONE;
		Stop(false);
		return;
	}


	m_pShareFolder = 0;
	m_sShareIndexBuffer.Empty();

	if ( CConfig::Instance()->GetSharedFolders(&m_SharedFolders) > 0 )
	{
		m_pSearchIndex->PrepareUpdate();

		if ( m_pFileNameSet )
		{
			m_pFileNameSet->clear();
			delete m_pFileNameSet;
		}
		m_pFileNameSet = new FileNameSet;

		m_pFileManagerInfo->m_nProgress = 0;
		m_pFileManagerInfo->m_eFileManagerStatus = efmsCREATESHARELIST;

		if ( CDownloadManager::Instance() )
			CDownloadManager::Instance()->SendFileManagerInfo(m_pFileManagerInfo);
	}
	else
	{
		m_pShareList->SetIndexBuffer( m_sShareIndexBuffer );
		m_pShareList->CreateList(m_pSearchIndex);

		m_pSearchIndex->SaveIndex();

		m_pFileManagerInfo->m_eFileManagerStatus = efmsNONE;

		Stop(false);
	}

}
