IsFWCheckUDPSearch(const CUInt128& target)
{

	SearchMap::const_iterator it = m_searches.find(target);
	if (it != m_searches.end()) {
		return (it->second->GetSearchTypes() == CSearch::NODEFWCHECKUDP);
	}
	return false;
}
