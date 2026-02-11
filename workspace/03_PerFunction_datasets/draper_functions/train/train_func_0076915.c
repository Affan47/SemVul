HandleNotification(const CMuleNotiferBase& ntf)
	{
		if (wxThread::IsMain()) {
#ifdef AMULE_DAEMON
			ntf.Notify();
#else

#if 0
			if (theApp->amuledlg) {
#else
			if (theApp && theApp->amuledlg) {
#endif

				ntf.Notify();
			}
#endif
		} else {
			CMuleGUIEvent evt(ntf.Clone());
			wxPostEvent(wxTheApp, evt);
		}
	}
