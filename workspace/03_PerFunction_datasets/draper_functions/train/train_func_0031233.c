erase( const std::string& item )
{
    if( ! m_hash.size() ) return;

    const int key = get_key( item );
    m_hash[ key ].erase( item );
}
