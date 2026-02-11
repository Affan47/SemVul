LoadMetFiles(const CPath& path)
{
	AddLogLineNS(CFormat(_("Loading temp files from %s.")) % path.GetPrintable());

	std::vector<CPath> files;


	CDirIterator TempDir(path);
	CPath fileName = TempDir.GetFirstFile(CDirIterator::File, wxT("*.part.met"));
	while (fileName.IsOk()) {
		files.push_back(path.JoinPaths(fileName));

		fileName = TempDir.GetNextFile();
	}


	std::sort(files.begin(), files.end());


	for ( size_t i = 0; i < files.size(); i++ ) {
		AddLogLineNS(CFormat(_("Loading PartFile %u of %u")) % (i + 1) % files.size());
		fileName = files[i].GetFullName();
		CPartFile *toadd = new CPartFile();
		bool result = toadd->LoadPartFile(path, fileName) != 0;
		if (!result) {

			result = toadd->LoadPartFile(path, fileName, true) != 0;
		}
		if (result && !IsFileExisting(toadd->GetFileHash())) {
			{
				wxMutexLocker lock(m_mutex);
				m_filelist.push_back(toadd);
			}
			NotifyObservers(EventType(EventType::INSERTED, toadd));
			Notify_DownloadCtrlAddFile(toadd);
		} else {
			wxString msg;
			if (result) {
				msg << CFormat(wxT("WARNING: Duplicate partfile with hash '%s' found, skipping: %s"))
					% toadd->GetFileHash().Encode() % fileName;
			} else {

				AddLogLineN(_("ERROR: Failed to load backup file. Search http://forum.amule.org for .part.met recovery solutions."));
				msg << CFormat(wxT("ERROR: Failed to load PartFile '%s'")) % fileName;
			}
			AddLogLineCS(msg);


			delete toadd;
		}
	}
	AddLogLineNS(_("All PartFiles Loaded."));

	if ( GetFileCount() == 0 ) {
		AddLogLineN(_("No part files found"));
	} else {
		AddLogLineN(CFormat(wxPLURAL("Found %u part file", "Found %u part files", GetFileCount())) % GetFileCount());

		DoSortByPriority();
		CheckDiskspace( path );
		Notify_ShowUpdateCatTabTitles();
	}
}
