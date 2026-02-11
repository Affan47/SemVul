slot_dropped_from_other( const CORE::DATA_INFO_LIST& list_info )
{
#ifdef _DEBUG
    std::cout << "BBSListViewBase:slot_dropped_from_other\n";
#endif

    CORE::DATA_INFO_LIST::const_iterator it = list_info.begin();
    for( ; it != list_info.end() ; ++it ){

        const CORE::DATA_INFO& info = ( *it );
        const int type = info.type;

        switch( type ){

            case TYPE_BOARD:
            case TYPE_BOARD_UPDATE:

                m_set_board.insert( DBTREE::url_boardbase( info.url ) );
                break;

            case TYPE_VBOARD:
                m_set_board.insert( info.url );
                break;

            case TYPE_THREAD:
            case TYPE_THREAD_UPDATE:
            case TYPE_THREAD_OLD:

                if( m_set_bookmark ) DBTREE::set_bookmarked_thread( info.url, true );
                m_set_thread.insert( DBTREE::url_dat( info.url ) );
                break;

            case TYPE_IMAGE:

                if( m_set_bookmark ) DBIMG::set_protect( info.url, true );
                m_set_image.insert( info.url );
                break;
        }
    }
}
