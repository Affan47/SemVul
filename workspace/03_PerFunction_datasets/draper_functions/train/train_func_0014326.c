startPrefetch(int idx)
{
#if QT_VERSION >= 0x040600
    if (idx < 0 || idx >= m_searchResults.size() || m_prefetches.contains(idx))
        return;
    m_prefetches[idx] = get(m_searchResults[idx]->description.url_o);
#else

    Q_UNUSED(idx);
#endif
}
