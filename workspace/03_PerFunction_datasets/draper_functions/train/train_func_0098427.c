slot_search_fin( const std::string& id )
{
    if( id != get_url() ) return;

#ifdef _DEBUG
    std::cout << "ArticleViewSearch::slot_search_fin " << get_url() << std::endl;
#endif

    m_loading = false;
    m_list_searchdata =  CORE::get_search_manager()->get_list_data();
    relayout();

    ARTICLE::get_admin()->set_command( "toggle_icon", get_url() );
}
