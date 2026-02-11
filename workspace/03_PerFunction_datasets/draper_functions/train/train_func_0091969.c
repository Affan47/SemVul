Remove(const char* pszKey)
{
    std::map<CPLString, GDALPDFObject*>::iterator oIter = m_map.find(pszKey);
    if (oIter != m_map.end())
    {
        delete oIter->second;
        m_map.erase(pszKey);
    }

    return *this;
}
