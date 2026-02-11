setName(const string* name) {
	delete m_Name;
	if (name != 0) {
		m_Name = new std::string(*name);
	} else {
		m_Name = 0;
	}
}
