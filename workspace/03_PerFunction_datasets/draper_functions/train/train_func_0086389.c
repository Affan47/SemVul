update_label()
{
    if( ! m_label ) return;

    if( m_length_prev != get_img()->current_length() ){

        m_length_prev = get_img()->current_length();

        char tmpstr[ 256 ];
        snprintf( tmpstr, 256, "%zd k / %zd k", m_length_prev/1024, get_img()->total_length()/1024 );
        m_label->set_text( tmpstr );
    }
}
