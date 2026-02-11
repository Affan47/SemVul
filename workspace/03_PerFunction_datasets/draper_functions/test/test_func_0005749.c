SetQualifier( string& name, string& value, uint32 listI ){
	if(listI < m_qualifierList.size()){
		delete m_qualifierList[ listI ];
		m_qualifierList[listI] = new gnStringQualifier(name, value);
		return true;
	}
	return false;
}
