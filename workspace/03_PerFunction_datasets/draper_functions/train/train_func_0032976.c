SetOSFiles(const wxString new_path)
{
	if ( thePrefs::IsOnlineSignatureEnabled() ) {
		if ( ::wxDirExists(new_path) ) {
			m_emulesig_path = JoinPaths(new_path, wxT("onlinesig.dat"));
			m_amulesig_path = JoinPaths(new_path, wxT("amulesig.dat"));
		} else {
			ShowAlert(_("The folder for Online Signature files you specified is INVALID!\n OnlineSignature will be DISABLED until you fix it on preferences."), _("ERROR"), wxOK | wxICON_ERROR);
			m_emulesig_path.Clear();
			m_amulesig_path.Clear();
		}
	} else {
		m_emulesig_path.Clear();
		m_amulesig_path.Clear();
	}
}
