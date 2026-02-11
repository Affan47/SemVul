CleanBuffers()
{

    if ( m_current_code_pnum != 0 )
        m_enc_pbuffer.CleanRetired( m_show_pnum, m_current_display_pnum );
}
