get_header_of_res( const int number )
{
    if( ! m_vec_header ) return NULL;
    if( number > m_max_res_number || number <= 0 ) return NULL;

    return m_vec_header[ number ];
}
