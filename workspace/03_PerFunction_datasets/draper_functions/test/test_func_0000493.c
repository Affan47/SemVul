tick_out( SAMPLE sample )
{
    if( !prepare_tick_out() )
        return FALSE;

    *m_data_ptr_out++ = sample;

    return TRUE;
}
