getProperty(const gchar * szName, const gchar *& szValue) const
{
	if (!m_pProperties)
		return false;
	const PropertyPair * pEntry = m_pProperties->pick(szName);

	if (!pEntry)
		return false;

	szValue = pEntry->first;
	return true;
}
