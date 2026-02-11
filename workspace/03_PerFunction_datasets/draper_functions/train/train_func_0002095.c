showExtraHelp() {
	cerr << "   Possible values: ";
	for (vector<int>::size_type i = 0; i < m_Values.size(); i++) {
		if (m_HasValue[i] != CMDLINE_UNSUPPORTED) {
			if (i != 0) cerr << ", ";
			cerr << m_Values[i];
		}
	}
	cerr << endl;
}
