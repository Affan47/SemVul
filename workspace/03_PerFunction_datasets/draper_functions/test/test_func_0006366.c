GetDBCache(const std::string &dbname)
{
	scoped_lock lock(m_map_mutex);

	MapType::iterator i = m_map.find(dbname);
	if( i != m_map.end() )
		return i->second;

	return DBCachePtr();
}
