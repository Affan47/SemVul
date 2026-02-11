CompleteFile(bool bIsHashingDone)
{
	if (GetKadFileSearchID()) {
		Kademlia::CSearchManager::StopSearch(GetKadFileSearchID(), false);
	}

	theApp->downloadqueue->RemoveLocalServerRequest(this);

	AddDebugLogLineN( logPartFile, wxString( wxT("CPartFile::CompleteFile: Hash ") ) + ( bIsHashingDone ? wxT("done") : wxT("not done") ) );

	if (!bIsHashingDone) {
		SetStatus(PS_COMPLETING);
		kBpsDown = 0.0;

		m_ADU_ext_kBpsDown  = 0.0;
		m_ADU_kadu_kBpsDown = 0.0;


		CPath partFile = m_partmetfilename.RemoveExt();
		CThreadScheduler::AddTask(new CHashingTask(GetFilePath(), partFile, this));
		return;
	} else {
		StopFile();
		m_is_A4AF_auto=false;
		SetStatus(PS_COMPLETING);


		PerformFileComplete();


	}
	if (thePrefs::ShowCatTabInfos()) {
		Notify_ShowUpdateCatTabTitles();
	}
	UpdateDisplayedInfo(true);
}
