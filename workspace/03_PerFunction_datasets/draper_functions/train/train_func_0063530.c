ParseSearchResultFolder( const CString & sContent )
{
	CMessageSearchResult * msg=0;
	CString s;
	int s1,s2,i1,slash,openBracket,closeBracket;


	if ( (s1=sContent.Find(' ')) < 0 )
		return 0;

	if ( (i1=sContent.Find(0x05,s1+1)) < 0 )
		return 0;

	if ( (s2=sContent.FindRev(' ',i1)) < 0 )
		return 0;

	msg = new CMessageSearchResult();

	msg->m_sNick = m_pRemoteToLocal->encode(sContent.Mid(0,s1));
	msg->m_sFile = m_pRemoteToLocal->encode(sContent.Mid(s1+1,s2-s1-1));
	msg->m_nSize = 0;


	s = sContent.Mid(s2+1,i1-s2-1);
	msg->m_nFreeSlot = 0;
	msg->m_nMaxSlot  = 0;

	if ( (slash = s.Find('/')) != -1 )
	{
		msg->m_nFreeSlot = s.Mid(0,slash).asUINT();
		msg->m_nMaxSlot  = s.Mid(slash+1,s.Length()-slash-1).asUINT();
	}

	s = sContent.Mid(i1+1,sContent.Length()-i1-1);

	if ( s.NotEmpty() )
	{
		if ( (closeBracket = s.FindRev(')')) != -1 )
		{
			if ( (openBracket = s.FindRev('('),closeBracket-1) != -1 )
			{
				if ( openBracket > 0 ) openBracket--;
				msg->m_sHubName = m_pRemoteToLocal->encode(s.Mid(0,openBracket));
				msg->m_sHubHost = s.Mid(openBracket+2,closeBracket-openBracket-2);
			}
		}
	}


	CString ip;
	unsigned int port;

	CNetAddr::ParseHost( msg->m_sHubHost, ip, port );

	msg->m_sHubHost = ip;

	if ( port != 0 )
	{
		 msg->m_sHubHost += ':';
		 msg->m_sHubHost += CString::number(port);
	}


	if ( msg->m_sHubName.StartsWith("TTH:",4) )
	{

		msg->m_sHash = msg->m_sHubName.Mid(4);

		msg->m_sHubName = msg->m_sHubHost;
	}


	msg->m_bFolder = true;

	return msg;
}
