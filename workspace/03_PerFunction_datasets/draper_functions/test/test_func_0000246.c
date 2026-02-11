slot_copy_url()
{
    SKELETON::View* view =  dynamic_cast< View* >( m_notebook->get_nth_page( m_clicked_page ) );
    if( view ) MISC::CopyClipboard( view->url_for_copy() );
}
