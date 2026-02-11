SaveConfigFile()
{
	if (!wxFileName::DirExists(GetConfigDir())) {
		wxFileName::Mkdir(GetConfigDir());
	}
	if (!m_configFile) {
		m_configFile = new CECFileConfig(m_configFileName);
	}
	if (m_configFile) {
		m_configFile->Write(wxT("/Locale"), m_language);
		m_configFile->Write(wxT("/EC/Host"), m_host);
		m_configFile->Write(wxT("/EC/Port"), m_port);
		m_configFile->WriteHash(wxT("/EC/Password"), m_password);
	}
}
