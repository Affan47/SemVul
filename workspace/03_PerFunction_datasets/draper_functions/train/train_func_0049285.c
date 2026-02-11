flushItem(const string &davLUID)
{

    EventCache::iterator it = m_cache.find(davLUID);
    if (it != m_cache.end()) {
        it->second->m_calendar.set(NULL);
    }
}
