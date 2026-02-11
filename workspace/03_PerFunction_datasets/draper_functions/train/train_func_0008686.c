createDataItem(PD_Document *pDoc, const char * szName)
{
	UT_return_val_if_fail(pDoc,NULL);
	UT_ASSERT(szName);

   	pDoc->createDataItem(szName, false, m_pbb, getMimeType(), NULL);
	return szName;
}
