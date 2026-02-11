search_cache( std::vector< ArticleBase* >& list_article,
                         const std::string& query, const bool mode_or, const bool bm, const bool& stop )
{
    std::list< BoardBase* >::iterator it;
    for( it = m_list_board.begin(); it != m_list_board.end(); ++it ){
        ( *it )->search_cache( list_article, query, mode_or, bm, stop );
        if( stop ) break;
    }
}
