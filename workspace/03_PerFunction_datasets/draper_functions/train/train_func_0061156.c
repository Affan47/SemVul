_event_SetDefaults(void)
{
	XAP_Prefs		*pPrefs;
	const gchar	*old_name;
	int currentPage;

	pPrefs = m_pApp->getPrefs();
	UT_return_if_fail (pPrefs);


	old_name = pPrefs->getCurrentScheme()->getSchemeName();

	currentPage = _gatherNotebookPageNum();

	pPrefs->setCurrentScheme("_builtin_");

	_populateWindowData();


	_setNotebookPageNum( currentPage );
	pPrefs->setCurrentScheme(old_name);
}
