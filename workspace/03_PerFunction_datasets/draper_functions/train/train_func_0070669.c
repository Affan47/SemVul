textIfSetted() {
	if(m_isDefaultValue && !hasChanged()) {
		return "";
	} else {
		return text();
	}
}
