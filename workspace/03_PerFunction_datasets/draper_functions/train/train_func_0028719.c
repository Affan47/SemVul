ResetCoordFilter()

{
    m_XMinFilter = m_poHeader->m_nXMin;
    m_YMinFilter = m_poHeader->m_nYMin;
    m_XMaxFilter = m_poHeader->m_nXMax;
    m_YMaxFilter = m_poHeader->m_nYMax;
    Int2Coordsys(m_XMinFilter, m_YMinFilter,
                 m_sMinFilter.x, m_sMinFilter.y);
    Int2Coordsys(m_XMaxFilter, m_YMaxFilter,
                 m_sMaxFilter.x, m_sMaxFilter.y);

    ORDER_MIN_MAX(int,m_XMinFilter,m_XMaxFilter);
    ORDER_MIN_MAX(int,m_YMinFilter,m_YMaxFilter);
    ORDER_MIN_MAX(double,m_sMinFilter.x,m_sMaxFilter.x);
    ORDER_MIN_MAX(double,m_sMinFilter.y,m_sMaxFilter.y);
}
