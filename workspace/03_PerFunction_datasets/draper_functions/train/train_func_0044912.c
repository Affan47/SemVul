initialize( )
{
    m_data = new SAMPLE[Digitalio::buffer_size() * Digitalio::num_channels_in()];
    memset( m_data, 0, Digitalio::buffer_size() * Digitalio::num_channels_in() * sizeof(SAMPLE) );

    m_data_ptr_in = Digitalio::m_use_cb ? m_data
        : (SAMPLE *)Digitalio::audio()->getStreamBuffer();

    m_data_max_in = m_data_ptr_in +
        Digitalio::buffer_size() * Digitalio::num_channels_in();

    Digitalio::m_read_ptr = &m_data_ptr_in;

    m_data_ptr_in = m_data_max_in;

    return TRUE;
}
