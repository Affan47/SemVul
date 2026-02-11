slot_usrcmd( int num )
{
    int res_num = 0;
    if( m_drawarea ) res_num =  m_drawarea->get_current_res_num();

    CORE::core_set_command( "exec_usr_cmd" ,m_url_article, MISC::itostr( num ), m_url_tmp, m_drawarea->str_selection(), MISC::itostr( res_num ) );
}
