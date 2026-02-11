get_urls()
{
    std::list< std::string > list_urls;
    for( int i = 1; i <= m_id_header; ++i ){

        NODE* head = res_header( i );
        if( head ){

            for( int block = 0; block < BLOCK_NUM; ++block ){

                NODE* node = head->headinfo->block[ block ];

                while( node ){
                    if( IS_URL( node ) ) list_urls.push_back( node->linkinfo->link );
                    node = node->next_node;
                }
            }
        }
    }

    return list_urls;
}
