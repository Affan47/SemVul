setBuffer( double* buffer, int stride, const QSize& size )
{
    if ( m_owner )
        delete[] m_buffer;

    m_buffer = buffer;
    m_owner = false;
    m_stride = stride;
    m_size = size;
    m_validRegions.clear();
}
