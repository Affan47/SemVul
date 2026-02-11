get( void * data, UINT__ num_elem, UINT__ read_offset_index )
{
    UINT__ i, j;
    BYTE__ * d = (BYTE__ *)data;


    if( read_offset_index >= m_read_offsets.size() )
        return 0;
    if( m_read_offsets[read_offset_index].read_offset < 0 )
        return 0;

    SINT__ m_read_offset = m_read_offsets[read_offset_index].read_offset;


    if( m_read_offset == m_write_offset )
        return 0;


    for( i = 0; i < num_elem; i++ )
    {
        for( j = 0; j < m_data_width; j++ )
        {
            d[i*m_data_width+j] = m_data[m_read_offset*m_data_width+j];
        }


        m_read_offset++;


        if( m_read_offset == m_write_offset )
        {
            i++;
            break;
        }


        if( m_read_offset >= m_max_elem )
            m_read_offset = 0;
    }


    m_read_offsets[read_offset_index].read_offset = m_read_offset;


    return i;
}
