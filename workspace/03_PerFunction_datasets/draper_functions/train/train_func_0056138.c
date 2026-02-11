setInputMode(const char * szName, bool bForce)
{
	UT_sint32 i;

	UT_DEBUGMSG(("XAP_App::setInputMode: %s %d\n", szName, bForce));

	UT_return_val_if_fail(m_pInputModes,-1);
	const char * szCurrentName = m_pInputModes->getCurrentMapName();
	if (!bForce && (g_ascii_strcasecmp(szName,szCurrentName) == 0))
		return 0;

	EV_EditEventMapper * p = m_pInputModes->getMapByName(szName);
	if (!p)
	{


		EV_EditBindingMap * pBindingMap = m_pApp->getBindingMap(szName);
		UT_return_val_if_fail(pBindingMap,-1);
		bool bResult;
		bResult = m_pInputModes->createInputMode(szName,pBindingMap);
		UT_return_val_if_fail(bResult,-1);
	}


	UT_DEBUGMSG(("Setting InputMode to [%s] for the current window.\n",szName));

	bool bStatus = m_pInputModes->setCurrentMap(szName);


	for (i = 0; i < getFrameCount(); i++) {
		getFrame(i)->getCurrentView()->notifyListeners(AV_CHG_INPUTMODE);
	}


	UT_DEBUGMSG(("XAP_App::setInputMode:: rebuilding menu's!"));
	rebuildMenus();

	return (bStatus);
}
