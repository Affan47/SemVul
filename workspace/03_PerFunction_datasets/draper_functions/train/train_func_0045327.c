OverwriteRecord(wxWindow *parent, iterator record)
{

	Barry::Builder *bp = dynamic_cast<Barry::Builder*> ((*record).get());
	if( !bp )
		return false;

cout << "Changing device record with index: 0x" << hex << (*record)->GetStateIndex() << endl;
cout << m_state << endl;

	DesktopInstancePtr dip = m_tdesktop.Get();
	Barry::Mode::Desktop &desktop = dip->Desktop();
bool iv = Barry::IsVerbose();
Barry::Verbose(true);
	try {
		desktop.SetRecord(m_dbid, (*record)->GetStateIndex(), *bp);
	} catch( Barry::ReturnCodeError &rce ) {
		if( rce.IsReadOnly() ) {
			ShowReadOnlyMsg(parent, rce);
			return false;
		}

		throw;
	}
Barry::Verbose(iv);

	return true;
}
