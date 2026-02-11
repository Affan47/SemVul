HasQualifier( const string& name ) const{
	for(uint32 i=0; i < m_qualifierList.size(); i++)
		if(m_qualifierList[i]->GetName() == name)
			return true;
	return false;
}
