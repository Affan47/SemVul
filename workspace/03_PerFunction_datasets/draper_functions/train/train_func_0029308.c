getNextColor() {
	if (m_ratsnestColorList.count() <= 0) return ErrorColor;

	int resetCount = 0;
	while (true) {
		if (m_index < 0 || m_index >= m_ratsnestColorList.count()) {
			m_index = 0;
			if (++resetCount > 2) {

				return ErrorColor;
			}
		}
		RatsnestColor * ratsnestColor = m_ratsnestColorList[m_index++];
		if (ratsnestColor->m_connectorNames.length() > 0) {

			m_index++;
			continue;
		}

		if (!ratsnestColor->m_ratsnest.isValid()){
			m_index++;
			continue;
		}

		return ratsnestColor->m_ratsnest;
	}
}
