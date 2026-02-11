setObjectByKey(const GLEStringKey& key, GLEDataObject* v) {
	GLEStringHashData::const_iterator i = m_Map.find(key);
	if (i != m_Map.end()) {
		GLEArrayImpl::setObject(i->second, v);
	} else {
		int len = size();
		ensure(len+1);
		GLEArrayImpl::setObject(len, v);
		m_Map.insert(pair<GLEStringKey, unsigned int>(key, len));
	}
}
