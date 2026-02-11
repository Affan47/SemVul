addHeaderValue(const std::string &name, const std::string &value)
{
    prepareHeaderValues();

    int idx = m_headerValues->size();

    ResponseValueIndex::iterator cit = m_headerValuesIndex->find(name);
    if (cit != m_headerValuesIndex->end()) {
        cit->second = idx;
    } else {
        m_headerValuesIndex->insert(std::make_pair(name, idx));
    }

    m_headerValues->push_back(std::make_pair(name, value));
}
