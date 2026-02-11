addLocalSubMap() {
	if (m_LocalMap == NULL) {
		m_LocalMap = new GLEVarMap();
		m_LocalMap->setTemp(true);
		var_alloc_local(0);
	}
	return m_LocalMap->pushSubMap();
}
