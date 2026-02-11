transformLog(bool xlog, bool ylog) {
	if (xlog) {
		for (unsigned int i = 0; i < size(); i++) {
			m_X[i] = log10(m_X[i]);
		}
	}
	if (ylog) {
		for (unsigned int i = 0; i < size(); i++) {
			m_Y[i] = log10(m_Y[i]);
		}
	}
}
