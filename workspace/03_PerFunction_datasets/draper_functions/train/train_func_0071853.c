OnClose(wxCloseEvent& evt)
{
	if (thePrefs::HideOnClose() && evt.CanVeto()) {
		Show(false);
		evt.Veto();
		return;
	}


	if (evt.CanVeto() && thePrefs::IsConfirmExitEnabled() ) {
		if (wxNO == wxMessageBox(wxString(CFormat(_("Do you really want to exit %s?")) % theApp->GetMuleAppName()),
				wxString(_("Exit confirmation")), wxYES_NO, this)) {
			evt.Veto();
			return;
		}
	}


#if !defined(CLIENT_GUI) && !defined(AMULE_DAEMON)

	if (theApp->m_AdunanzAStreaming.m_status != CAdunanzAStreaming::None) theApp->m_AdunanzAStreaming.stop();
#endif

	SaveGUIPrefs();

	Enable(false);
	Show(false);

	theApp->ShutDown(evt);
}
