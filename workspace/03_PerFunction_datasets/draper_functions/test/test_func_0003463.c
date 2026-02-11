normalize() {
	if (m_XMin > m_XMax) {
		double a = m_XMin;
		m_XMin = m_XMax;
		m_XMax = a;
	}
	if (m_YMin > m_YMax) {
		double a = m_YMin;
		m_YMin = m_YMax;
		m_YMax = a;
	}
}
