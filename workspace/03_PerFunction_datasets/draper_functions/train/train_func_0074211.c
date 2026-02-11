addParam(const string& name, int type) {
	int len = name.length();
	if (len > 1 && name[len-1] == '$') {
		string shortname = name;
		shortname.erase(len-1);
		m_PNameS.push_back(shortname);
	} else {
		m_PNameS.push_back(name);
	}
	m_PName.push_back(name);
	m_PType.push_back(type);
	m_PDefault.push_back("");
}
