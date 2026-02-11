setAll(int value)
{
    m_vector->fill(value);
    m_count = value ? size() : 0;
    m_cache.first = m_cache.second = -1;
}
