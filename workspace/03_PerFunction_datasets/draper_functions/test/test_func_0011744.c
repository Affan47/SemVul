clear()
{
    if( m_rawdata ) free( m_rawdata );
    m_rawdata = NULL;

    if( m_rawdata_left ) free( m_rawdata_left );
    m_rawdata_left = NULL;

    m_lng_rawdata = 0;
    m_lng_rawdata_left = 0;

    m_get_article_url = std::string();

    if( m_iconv ) delete m_iconv;
    m_iconv = NULL;

    m_list_artinfo.clear();
}
