ClearAllData(void) {
    BamToolsIndexData::const_iterator indexIter = m_indexData.begin();
    BamToolsIndexData::const_iterator indexEnd  = m_indexData.end();
    for ( ; indexIter != indexEnd; ++indexIter ) {
        const int& refId = (*indexIter).first;
        ClearReferenceOffsets(refId);
    }
}
