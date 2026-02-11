getRoot(const char* name) {
	GLERC<GLEString> strName(new GLEString(name));
	return (GLESubRoot*)m_SubRoots->getObjectByKey(strName);
}
