GetFirstFeature()
{
    if (m_nFeatureCount < 0) {
        m_poReader->ReadDataRecords(this);
    }

    if (m_bGeometryPerBlock && !m_bGeometry) {
        LoadGeometry();
    }

    if (m_nFeatureCount < 1)
        return NULL;

    return m_papoFeature[0];
}
