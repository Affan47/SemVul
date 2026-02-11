initialize( UINT__ num_elem, UINT__ width )
{

    cleanup();


    m_data = (BYTE__ *)malloc( num_elem * width );
    if( !m_data )
        return false;

    m_data_width = width;

    m_write_offset = 0;
    m_max_elem = (SINT__)num_elem;

    return true;
}
