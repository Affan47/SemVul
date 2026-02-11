GetUploadFileInfo()
{

	wxString sRet;
	sRet = (CFormat(_("NickName: %s ID: %u")) % GetUserName() % GetUserIDHybrid()) + wxT(" ");
	if (m_reqfile) {
		sRet += CFormat(_("Requested: %s\n")) % m_reqfile->GetFileName();
		sRet += CFormat(
				wxPLURAL("Filestats for this session: Accepted %d of %d request, %s transferred\n", "Filestats for this session: Accepted %d of %d requests, %s transferred\n", m_reqfile->statistic.GetRequests())
				) % m_reqfile->statistic.GetAccepts() % m_reqfile->statistic.GetRequests() % CastItoXBytes(m_reqfile->statistic.GetTransferred());
		sRet += CFormat(
				wxPLURAL("Filestats for all sessions: Accepted %d of %d request, %s transferred\n", "Filestats for all sessions: Accepted %d of %d requests, %s transferred\n", m_reqfile->statistic.GetAllTimeRequests())
				) % m_reqfile->statistic.GetAllTimeAccepts() % m_reqfile->statistic.GetAllTimeRequests() % CastItoXBytes(m_reqfile->statistic.GetAllTimeTransferred());
	} else {
		sRet += _("Requested unknown file");
	}
	return sRet;
}
