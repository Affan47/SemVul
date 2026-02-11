addPointIPol(double x) {
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
				m_PrevPoint = false;
				m_PrevInvalid = false;
			}
			m_CrEnable = (wval != 0.0);
		}
		if (m_CrEnable) {
			if (m_FineTune) {
				addPointFineTune(x, lr);
			} else {
				addPoint();
			}
			m_PrevPoint = true;
			m_PrevXValue = x;
		}
		if (more) {
			tryAddMissing(x, lr);
			lr++;
		} else {
			break;
		}
	}
}
