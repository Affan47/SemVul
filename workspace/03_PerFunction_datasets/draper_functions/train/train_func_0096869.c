restore_history( const std::string& url_history )
{
    if( url_history == URL_HISTCLOSEVIEW && m_menu_close ) m_menu_close->restore_history();
    if( url_history == URL_HISTCLOSEBOARDVIEW && m_menu_closeboard ) m_menu_closeboard->restore_history();
    if( url_history == URL_HISTCLOSEIMGVIEW && m_menu_closeimg ) m_menu_closeimg->restore_history();
}
