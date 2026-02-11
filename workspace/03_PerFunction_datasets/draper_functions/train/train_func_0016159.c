s_onMenuItemDeselect(GtkWidget * , gpointer data)
	{
		UT_ASSERT(data);

		_wd * wd = static_cast<_wd *>(data);
		UT_return_if_fail(wd && wd->m_pUnixMenu);

		XAP_Frame * pFrame = wd->m_pUnixMenu->getFrame();
		UT_return_if_fail(pFrame);

		pFrame->setStatusMessage(NULL);
	}
