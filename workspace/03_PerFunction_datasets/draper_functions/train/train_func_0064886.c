get_toolbar( int page )
{
    return dynamic_cast< SKELETON::ToolBar* >( m_notebook_toolbar.get_nth_page( page ) );
}
