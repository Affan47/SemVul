includes(const string& file) {
	for (vector<GLESourceFile*>::size_type i = 0; i < m_Files.size(); i++) {
		if (str_i_equals(m_Files[i]->getLocation()->getName(), file)) return true;
	}
	return false;
}
