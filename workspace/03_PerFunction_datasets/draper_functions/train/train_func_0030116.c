cacheSize() const
{
    Locker locker(m_Mutex);
    AVM_WRITE("ASF network reader", 1, "cacheSize()   finished: %d\n", m_bFinished);
    if (m_bFinished) return 1.;

    size_t min = m_Iterators.size() ? CACHE_PACKETS : 0;
    for(avm::vector<NetworkIterator*>::const_iterator it2 = m_Iterators.begin();
	it2!=m_Iterators.end(); it2++)
    {
	size_t s = (*it2)->m_Packets.size();

	if (s < min)
            min = s;
    }

    return (double)min / (double)CACHE_PACKETS;
}
