SaveDCPublicHub()
{
	int err=0;
	CString s;
	CXml * xml = new CXml();
	DCConfigHubItem *hubitem;

	xml->NewDoc( XML_DCHUB_CONFIG );


	xml->StartNewChild( XML_SERVER );


	if ( bHubListStoreLocal )
	{
		hubitem = 0;

		while( pPublicHubList->Next(&hubitem) != 0 )
		{
			xml->StartNewChild( XML_PUBLIC );
			xml->NewNumericChild( XML_ID,	       hubitem->m_nID );
			xml->NewStringChild(  XML_NAME,        hubitem->m_sName );
			xml->NewStringChild(  XML_HOST,        hubitem->m_sHost );
			xml->NewStringChild(  XML_DESCRIPTION, hubitem->m_sDescription );
			xml->NewNumericChild( XML_USERCOUNT,   hubitem->m_nUserCount );
			xml->NewStringChild(  XML_COUNTRY,     hubitem->m_sCountry );
			xml->NewStringChild(  XML_EXTRA,       hubitem->m_sExtra );
			xml->NewNumericChild( XML_SHARED,      hubitem->m_nShared );
			xml->NewNumericChild( XML_MINSHARE,    hubitem->m_nMinShare );
			xml->Parent();
		}
	}

	xml->Parent();


	s = sConfigPath + DCHUB_CONFIG;

	if ( xml->SaveConfigXmlViaTemp(s) == -1 )
	{
		err = -1;
	}

	delete xml;

	return err;
}
