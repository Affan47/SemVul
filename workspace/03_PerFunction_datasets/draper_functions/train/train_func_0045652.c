DownloadCtrlUpdateItem(const void* item)
	{
#ifndef CLIENT_GUI


#  if 0
		theApp->ECServerHandler->m_ec_notifier->DownloadFile_SetDirty((CPartFile *)item);
#  else
		theApp->ECServerHandler->m_ec_notifier->DownloadFile_SetDirty(static_cast<const CPartFile*>(item));
#  endif


#endif
#ifndef AMULE_DAEMON

#if 0
		if (theApp->amuledlg->m_transferwnd && theApp->amuledlg->m_transferwnd->downloadlistctrl) {
#else
		if (theApp && theApp->amuledlg->m_transferwnd && theApp->amuledlg->m_transferwnd->downloadlistctrl) {
#endif

			theApp->amuledlg->m_transferwnd->downloadlistctrl->UpdateItem(item);
		}
#endif
	}
