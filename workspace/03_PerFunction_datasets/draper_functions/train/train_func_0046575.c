resize(int n) {
	int add = n - m_Elems.size() + 1;
	while (add > 0) {
		m_Elems.push_back(false);
		add--;
	}
}
