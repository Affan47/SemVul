slot_switch_page( GtkNotebookPage*, guint page )
{
    if( m_notebook.get_nth_page( page ) == m_localrule ){
        m_localrule->set_command( "clear_screen" );
        m_localrule->set_command( "append_html", DBTREE::localrule( get_url() ) );
    }
}
