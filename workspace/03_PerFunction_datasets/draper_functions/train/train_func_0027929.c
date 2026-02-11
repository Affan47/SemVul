PrintMessage(const wxString& msg, int type)
{
	XRCCTRL(*this, "ID_RESULTS", wxTextCtrl)->AppendText(msg + _T("\n"));
}
