ParseLogedIn( CString sContent )
{
	CMessageLogedIn * msg = new CMessageLogedIn();


	if ( sContent.NotEmpty() && (sContent.Data()[0] == ' ') )
	{
		sContent = sContent.Mid(1,sContent.Length()-1);
	}

	msg->m_sNick = m_pRemoteToLocal->encode(sContent);

	return msg;
}
