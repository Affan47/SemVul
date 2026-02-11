drawTypeAheadItems() {

    for (size_t i = 0; i < m_matches.size(); i++)
        clearItem(m_matches[i]->getIndex(), true, m_matches.size());

    m_matches = m_type_ahead.matched();
    for (size_t j = 0; j < m_matches.size(); j++)
        clearItem(m_matches[j]->getIndex(), false, j);
}
