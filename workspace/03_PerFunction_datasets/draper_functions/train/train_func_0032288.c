event_Load ()
{
	XAP_DialogFactory * pDialogFactory
		= static_cast<XAP_DialogFactory *>(m_pFrame->getDialogFactory());

	XAP_Dialog_FileOpenSaveAs * pDialog
		= static_cast<XAP_Dialog_FileOpenSaveAs *>(pDialogFactory->requestDialog(XAP_DIALOG_ID_FILE_OPEN));
	UT_return_if_fail(pDialog);


	UT_String pluginDir (XAP_App::getApp()->getUserPrivateDirectory());
	pluginDir += "/";
	pluginDir += PACKAGE_NAME;
	pluginDir += "-";
	pluginDir += ABIWORD_SERIES;
	pluginDir += "/plugins/";
	pDialog->setCurrentPathname (pluginDir.c_str());
	pDialog->setSuggestFilename(false);

	UT_uint32 filterCount = 1;
	const char ** szDescList = static_cast<const char **>(UT_calloc(filterCount + 1,
																	sizeof(char *)));
	const char ** szSuffixList = static_cast<const char **>(UT_calloc(filterCount + 1,
																	  sizeof(char *)));
	IEFileType * nTypeList = static_cast<IEFileType *>(UT_calloc(filterCount + 1,
																 sizeof(IEFileType)));

	szDescList[0] = "AbiWord Plugin (.G_MODULE_SUFFIX)";
	szSuffixList[0] = "*.G_MODULE_SUFFIX";
	nTypeList[0] = static_cast<IEFileType>(1);

	pDialog->setFileTypeList(szDescList, szSuffixList,
							 static_cast<const UT_sint32 *>(nTypeList));

	pDialog->setDefaultFileType(static_cast<IEFileType>(1));

	pDialog->runModal(m_pFrame);

	XAP_Dialog_FileOpenSaveAs::tAnswer ans = pDialog->getAnswer();
	bool bOK = (ans == XAP_Dialog_FileOpenSaveAs::a_OK);

	if (bOK)
    {
		const char * szResultPathname = pDialog->getPathname();
		if (szResultPathname && *szResultPathname)
		{
			if (activatePlugin (szResultPathname))
			{

				_updatePluginList ();
			}
			else
			{

				_errorMessage (m_pFrame,
							   XAP_STRING_ID_DLG_PLUGIN_MANAGER_COULDNT_LOAD);
			}
		}
    }

	FREEP(szDescList);
	FREEP(szSuffixList);
	FREEP(nTypeList);

	pDialogFactory->releaseDialog(pDialog);
}
