addPoint(double x) {
	int lr = GLE_DS_L;
	while (true) {
		bool more = selectXValue(x, lr);
		if (!more && m_MissX.find(x) != m_MissX.end()) {
			addMissingLR(x, lr);
			return;
		}
		if (m_Where != NULL) {
			double wval = m_Where->evalDouble();
			if (m_CrEnable && wval == 0.0) {

				addMissingLR(x, lr);
			}
			m_CrEnable = (wval != 0.0);
		}
		if (m_CrEnable) addPoint();
		if (more) {
			tryAddMissing(x, lr);
			lr++;
		} else {
			break;
		}
	}
}
