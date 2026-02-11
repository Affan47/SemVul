find( const std::string& datbase, const std::string& id )
{
    if( ! m_table.size() ) return NULL;

    const size_t hash = get_hash( id );

    std::vector< ArticleBase* >::iterator it = m_table[ hash ].begin();
    for( ; it != m_table[ hash ].end(); ++it ) if( ( *it )->equal( datbase, id ) ) return *it;

    return NULL;
}
