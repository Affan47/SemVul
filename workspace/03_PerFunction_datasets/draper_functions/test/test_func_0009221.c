FlattenGlyphList(std::vector<utf16> & vgidFlattened)
{
	if (!m_fHasFlatList)
		FlattenMyGlyphList();
	for (size_t igid = 0; igid < m_vgidFlattened.size(); igid++)
	{
		vgidFlattened.push_back(m_vgidFlattened[igid]);
	}
}
