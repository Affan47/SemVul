allDefaults() {
	for (vector<CmdLineOption*>::size_type i = 0; i < m_Options.size(); i++) {
		if (m_Options[i] != NULL) {
			if (!m_Options[i]->allDefaults()) return false;
		}
	}
	return true;
}
