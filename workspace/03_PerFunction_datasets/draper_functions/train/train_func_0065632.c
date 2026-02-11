initialize_synthesis( )
{
    if( !m_init )
    {
        m_last_error = "VM initialize_synthesis() called on raw VM";
        return FALSE;
    }

    if( !g_t_dac || !g_t_adc )
    {
        m_last_error = "VM initialize_synthesis() called before type system initialized";
        return FALSE;
    }

    if( m_dac != NULL )
    {
        m_last_error = "VM synthesis already initialized";
        return FALSE;
    }


    EM_log( CK_LOG_SYSTEM, "initializing synthesis engine..." );

    EM_pushlog();


    EM_log( CK_LOG_SEVERE, "initializing 'dac'..." );

    g_t_dac->ugen_info->num_outs =
        g_t_dac->ugen_info->num_ins = m_num_dac_channels;
    m_dac = (Chuck_UGen *)instantiate_and_initialize_object( g_t_dac, NULL );
    stereo_ctor( m_dac, NULL, NULL );
    multi_ctor( m_dac, NULL, NULL );
    m_dac->add_ref();

    m_dac->lock();


    EM_log( CK_LOG_SEVERE, "initializing 'adc'..." );
    g_t_dac->ugen_info->num_ins =
        g_t_adc->ugen_info->num_outs = m_num_adc_channels;
    m_adc = (Chuck_UGen *)instantiate_and_initialize_object( g_t_adc, NULL );
    stereo_ctor( m_adc, NULL, NULL );
    multi_ctor( m_adc, NULL, NULL );
    m_adc->add_ref();

    m_adc->lock();


    EM_log( CK_LOG_SEVERE, "initializing 'blackhole'..." );
    m_bunghole = new Chuck_UGen;
    m_bunghole->add_ref();
    m_bunghole->lock();
    initialize_object( m_bunghole, &t_ugen );
    m_bunghole->tick = NULL;
    m_shreduler->m_dac = m_dac;
    m_shreduler->m_adc = m_adc;
    m_shreduler->m_bunghole = m_bunghole;
    m_shreduler->m_num_dac_channels = m_num_dac_channels;
    m_shreduler->m_num_adc_channels = m_num_adc_channels;


    EM_log( CK_LOG_SYSTEM, "initializing '%s' audio...", m_audio ? "real-time" : "fake-time" );

    if( !m_bbq->initialize( m_num_dac_channels, m_num_adc_channels,
        Digitalio::m_sampling_rate, 16,
        Digitalio::m_buffer_size, Digitalio::m_num_buffers,
        Digitalio::m_dac_n, Digitalio::m_adc_n,
        m_block, this, m_audio ) )
    {
        m_last_error = "cannot initialize audio device (try using --silent/-s)";

        EM_poplog();
        return FALSE;
    }


    EM_poplog();

    return TRUE;
}
