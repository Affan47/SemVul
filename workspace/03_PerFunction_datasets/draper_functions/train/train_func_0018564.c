abi_widget_load_file(AbiWidget * w, const gchar * pszFile, const gchar * extension_or_mimetype)
{
	UT_DEBUGMSG(("abi_widget_load_file() - file: %s\n", pszFile));

	UT_return_val_if_fail(w && w->priv, false);

	IEFileType ieft = s_abi_widget_get_file_type(extension_or_mimetype, NULL, 0, true);
	UT_DEBUGMSG(("Will use ieft %d to load file\n", ieft));

	bool res = false;
	if (w->priv->m_bMappedToScreen)
	{
		UT_return_val_if_fail(w->priv->m_pFrame, FALSE);
		AP_UnixFrame * pFrame = w->priv->m_pFrame;

		s_StartStopLoadingCursor( true, pFrame);
		pFrame->setCursor(GR_Graphics::GR_CURSOR_WAIT);

		UT_DEBUGMSG(("Attempting to load %s \n", pszFile));
		res = (pFrame->loadDocument(pszFile, ieft, true) == UT_OK);

		FV_View * pView = static_cast<FV_View *>(pFrame->getCurrentView());
		w->priv->m_pDoc = pView->getDocument();

		s_StartStopLoadingCursor( false, pFrame);
	}
	else
	{
		UT_DEBUGMSG(("Attempting to load %s \n", pszFile));


		w->priv->m_pDoc = new PD_Document();
		w->priv->m_pDoc->readFromFile(pszFile, ieft);
	}

	if (w->priv->m_bUnlinkFileAfterLoad)
	{
		remove(pszFile);
		w->priv->m_bUnlinkFileAfterLoad = false;
	}

	return res;
}
