unloadData()
{
    delete[] m_area_map;
    delete[] m_V9;
    delete[] m_V8;
    delete[] m_liquidEntry;
    delete[] m_liquidFlags;
    delete[] m_liquid_map;

    m_area_map = NULL;
    m_V9 = NULL;
    m_V8 = NULL;
    m_liquidEntry = NULL;
    m_liquidFlags = NULL;
    m_liquid_map  = NULL;
    m_gridGetHeight = &GridMap::getHeightFromFlat;
}
