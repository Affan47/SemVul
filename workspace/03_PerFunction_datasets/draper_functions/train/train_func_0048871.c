slot_close_tab()
{
    if( m_clicked_page < 0 ) return;

#ifdef _DEBUG
    std::cout << "Admin::slot_close_tab " << m_clicked_page << std::endl;
#endif

    SKELETON::View* view =  dynamic_cast< View* >( m_notebook->get_nth_page( m_clicked_page ) );
    if( view ) close_view( view->get_url() );
}
