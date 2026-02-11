SetDNAttr(const LdifAttribute &name)
{

	AccessMapType::iterator i = m_map.find(name);
	if( i == m_map.end() )
		return false;

	m_dnAttr = name;
	return true;
}
