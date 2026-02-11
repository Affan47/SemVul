ChatUpdateFriend(CFriend * NOT_ON_DAEMON(toupdate))
	{
#ifndef AMULE_DAEMON
		if (theApp->amuledlg->m_chatwnd) {
			theApp->amuledlg->m_chatwnd->UpdateFriend(toupdate);
		}
#endif
	}
