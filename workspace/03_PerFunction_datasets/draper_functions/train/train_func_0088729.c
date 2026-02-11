equals(GLEDataObject* obj) {
	if (obj->getType() != GLEObjectTypeString) return false;
	GLEString* other = (GLEString*)obj;
	if (m_Length != other->length()) return false;
	for (unsigned int i = 0; i < m_Length; i++) {
		if (get(i) != other->get(i)) return false;
	}
	return true;
}
