getSubDescription(const string &davLUID, const string &subid)
{
    EventCache::iterator it = m_cache.find(davLUID);
    if (it == m_cache.end()) {

        return "";
    } else {
        return getSubDescription(*it->second, subid);
    }
}
