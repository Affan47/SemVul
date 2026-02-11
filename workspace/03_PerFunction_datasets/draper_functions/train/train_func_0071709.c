setWireFlag(bool setting, WireFlag flag) {
	if (setting) {
		m_wireFlags |= flag;
	}
	else {
		m_wireFlags &= ~flag;
	}
}
