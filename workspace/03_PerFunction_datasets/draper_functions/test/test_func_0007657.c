valid(double x, double y) {
	if (m_HasXMin && x < m_XMin) return false;
	if (m_HasXMax && x > m_XMax) return false;
	if (m_HasYMin && y < m_YMin) return false;
	if (m_HasYMax && y < m_YMax) return false;
	return true;
}
