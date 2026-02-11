Check_and_Init_Skin()
{
	bool ret = true;
	wxString skinFileName(thePrefs::GetSkin());

	if (skinFileName.IsEmpty() || skinFileName.IsSameAs(_("- default -"))) {
		return false;
	}

	wxString userDir(JoinPaths(GetConfigDir(), wxT("skins")) + wxFileName::GetPathSeparator());

	wxStandardPathsBase &spb(wxStandardPaths::Get());
#ifdef __WXMSW__
	wxString dataDir(spb.GetPluginsDir());
#elif defined(__WXMAC__)
		wxString dataDir(spb.GetDataDir());
#else
	wxString dataDir(spb.GetDataDir().BeforeLast(wxT('/')) + wxT("/amule"));
#endif
	wxString systemDir(JoinPaths(dataDir,wxT("skins")) + wxFileName::GetPathSeparator());


	skinFileName.Replace(wxT("User:"), userDir );
	skinFileName.Replace(wxT("System:"), systemDir );

	m_skinFileName.Assign(skinFileName);
	if (!m_skinFileName.FileExists()) {
		AddLogLineC(CFormat(
			_("Skin directory '%s' does not exist")) %
			skinFileName );
		ret = false;
	} else if (!m_skinFileName.IsFileReadable()) {
		AddLogLineC(CFormat(
			_("WARNING: Unable to open skin file '%s' for read")) %
			skinFileName);
		ret = false;
	}

	wxFFileInputStream in(m_skinFileName.GetFullPath());
	wxZipInputStream zip(in);

	while ((entry = zip.GetNextEntry()) != NULL) {
		wxZipEntry*& current = cat[entry->GetInternalName()];
		delete current;
		current = entry;
	}

	return ret;
}
