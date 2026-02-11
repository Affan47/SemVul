createInputMode(const char * szName,
										EV_EditBindingMap * pBindingMap)
{
	UT_ASSERT(szName && *szName);
	UT_ASSERT(pBindingMap);

	char * szDup = NULL;
	EV_EditEventMapper * pEEM = NULL;

	szDup = g_strdup(szName);
	UT_ASSERT(szDup);

	pEEM = new EV_EditEventMapper(pBindingMap);
	UT_ASSERT(pEEM);

	bool b1;
	b1 = (m_vecEventMaps.addItem(pEEM) == 0);
	bool b2;
	b2 = (m_vecNames.addItem(szDup) == 0);
	UT_ASSERT(b1 && b2);
	UT_UNUSED(b1);
	UT_UNUSED(b2);

	return true;
}
