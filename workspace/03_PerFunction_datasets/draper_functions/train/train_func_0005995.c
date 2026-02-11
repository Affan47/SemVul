HasAlignments(const int& refId) const {
    BamStandardIndexData::const_iterator indexIter = m_indexData.find(refId);
    if ( indexIter == m_indexData.end() ) return false;
    const ReferenceIndex& refEntry = (*indexIter).second;
    return refEntry.HasAlignments;
}
