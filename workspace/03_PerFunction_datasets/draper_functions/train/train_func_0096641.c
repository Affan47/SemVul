tick_in( SAMPLE * s )
{
    if( !m_data )
        return FALSE;

    *s = *m_ptr_curr++;

    return TRUE;
}
