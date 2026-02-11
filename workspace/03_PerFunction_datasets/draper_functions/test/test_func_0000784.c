stop_load()
{
#ifdef _DEBUG
    std::cout << "Img::stop_load url = " << m_url << std::endl;
#endif

    SKELETON::Loadable::stop_load();

    if( m_wait ){

        set_code( HTTP_TIMEOUT );
        set_str_code( "stop loading" );

        reset_wait();
    }
}
