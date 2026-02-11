getObject(int var) {
	if (check(&var)) {
		return NULL;
	} else {
		return (GLEDataObject*)m_Global.getObject(var);
	}
}
