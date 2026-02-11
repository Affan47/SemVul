addStream(uint_t id, const avm::vector<uint32_t>& table)
{
    if (!m_pCache)
	m_pCache = new Cache();
    return (m_pCache) ? m_pCache->addStream(id, table) : -1;
}
