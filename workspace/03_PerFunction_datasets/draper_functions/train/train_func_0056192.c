OnOK(wxCommandEvent& evt)
{
	wxString s_port = CastChild(ID_REMOTE_PORT, wxTextCtrl)->GetValue();
	port = StrToLong(s_port);

	host = CastChild(ID_REMOTE_HOST, wxTextCtrl)->GetValue();
	passwd = CastChild(ID_EC_PASSWD, wxTextCtrl)->GetValue();

	if (passwd != pwd_hash) {
		pwd_hash = MD5Sum(passwd).GetHash();
	}
	m_save_user_pass = CastChild(ID_EC_SAVE, wxCheckBox)->IsChecked();
	evt.Skip();
}
