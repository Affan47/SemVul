Delete()
{
	AddLogLineN(CFormat(_("Deleting file: %s")) % GetFileName());

	StopFile(true);
	AddDebugLogLineN(logPartFile, wxT("\tStopped"));

#ifdef __DEBUG__
	uint16 removed =
#endif
		theApp->uploadqueue->SuspendUpload(GetFileHash(), true);
	AddDebugLogLineN(logPartFile, CFormat(wxT("\tSuspended upload to %d clients")) % removed);
	theApp->sharedfiles->RemoveFile(this);
	AddDebugLogLineN(logPartFile, wxT("\tRemoved from shared"));
	theApp->downloadqueue->RemoveFile(this);
	AddDebugLogLineN(logPartFile, wxT("\tRemoved from download queue"));
	Notify_DownloadCtrlRemoveFile(this);
	AddDebugLogLineN(logPartFile, wxT("\tRemoved from transferwnd"));
	if (theApp->canceledfiles->Add(GetFileHash())) {
		theApp->canceledfiles->Save();
	}
	AddDebugLogLineN(logPartFile, wxT("\tAdded to canceled file list"));
	theApp->searchlist->UpdateSearchFileByHash(GetFileHash());

	if (m_hpartfile.IsOpened()) {
		m_hpartfile.Close();
	}

	AddDebugLogLineN(logPartFile, wxT("\tClosed"));

	if (!CPath::RemoveFile(m_fullname)) {
		AddDebugLogLineC(logPartFile, CFormat(wxT("\tFailed to delete '%s'")) % m_fullname);
	} else {
		AddDebugLogLineN(logPartFile, wxT("\tRemoved .part.met"));
	}

	if (!CPath::RemoveFile(m_PartPath)) {
		AddDebugLogLineC(logPartFile, CFormat(wxT("Failed to delete '%s'")) % m_PartPath);
	} else {
		AddDebugLogLineN(logPartFile, wxT("\tRemoved .part"));
	}

	CPath BAKName = m_fullname.AppendExt(PARTMET_BAK_EXT);
	if (!CPath::RemoveFile(BAKName)) {
		AddDebugLogLineC(logPartFile, CFormat(wxT("Failed to delete '%s'")) % BAKName);
	} else {
		AddDebugLogLineN(logPartFile, wxT("\tRemoved .bak"));
	}

	CPath SEEDSName = m_fullname.AppendExt(wxT(".seeds"));
	if (SEEDSName.FileExists()) {
		if (CPath::RemoveFile(SEEDSName)) {
			AddDebugLogLineN(logPartFile, wxT("\tRemoved .seeds"));
		} else {
			AddDebugLogLineC(logPartFile, CFormat(wxT("Failed to delete '%s'")) % SEEDSName);
		}
	}

	AddDebugLogLineN(logPartFile, wxT("Done"));

	delete this;
}
