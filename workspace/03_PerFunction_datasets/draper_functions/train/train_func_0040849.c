isPartLabelVisible() {
	if (m_partLabel == NULL) return false;
	if (!hasPartLabel()) return false;
	if (!m_partLabel->initialized()) return false;

	return m_partLabel->isVisible();
}
