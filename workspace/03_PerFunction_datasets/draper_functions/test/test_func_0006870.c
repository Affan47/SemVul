Search_Add_Result(CSearchFile* NOT_ON_DAEMON(result))
	{
#ifndef AMULE_DAEMON
		if (theApp->amuledlg && theApp->amuledlg->m_searchwnd) {
			theApp->amuledlg->m_searchwnd->AddResult(result);
		}
#endif
	}
