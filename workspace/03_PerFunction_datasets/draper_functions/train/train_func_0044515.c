SendPrivateMessage( CString sNick, CString sTo, CString sMsg, CString sFromNick )
{
	DCProtoMutex.Lock();

	CString t = "$To: ";
	t += m_pLocalToRemote->encode(sTo);
	t += " From: ";
	t += m_pLocalToRemote->encode(sNick);
	t += " $<";
	if ( sFromNick.IsEmpty() )
		t += m_pLocalToRemote->encode(sNick);
	else
		t += m_pLocalToRemote->encode(sFromNick);

	sMsg = sMsg.Replace( "$", "&#36;");
	sMsg = sMsg.Replace( "|", "&#124;");
	sMsg = m_pLocalToRemote->encode(sMsg);

	t += "> ";
	t += sMsg;
	t += '|';

	const int err = Write((const unsigned char*)t.Data(),t.Length());

	DCProtoMutex.UnLock();

	return err;
}
