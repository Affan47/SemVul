isValid() const
{
    unsigned size = m_sources.size();
    if (!size)
        return false;
    for (unsigned i = 0; i < size; i++) {
        if (m_sources[i]->isValid())
            return true;
    }
    return false;
}
