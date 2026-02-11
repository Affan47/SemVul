tick_in( SAMPLE * l, SAMPLE * r )
{
    if( !m_data || m_ptr_curr + 2 >= m_ptr_end )
        return FALSE;

    *l = *m_ptr_curr++;
    *r = *m_ptr_curr++;

    return TRUE;
}
