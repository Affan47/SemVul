readProperty(const string &property) const
{
    ConfigFilter::const_iterator it = m_filter.find(property);

    if (it != m_filter.end()) {
        return it->second;
    } else {
        return m_readOnlyNode->readProperty(property);
    }
}
