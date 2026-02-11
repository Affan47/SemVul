slot_open_by_browser()
{
#ifdef _DEBUG
    std::cout << "Admin::slot_open_by_browser " << m_clicked_page << std::endl;
#endif

    SKELETON::View* view =  dynamic_cast< View* >( m_notebook->get_nth_page( m_clicked_page ) );
    if( view ) CORE::core_set_command( "open_url_browser", view->url_for_copy() );
}
