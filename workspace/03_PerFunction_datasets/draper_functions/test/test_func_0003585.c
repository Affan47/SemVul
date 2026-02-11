get_size( int& width, int& height )
{
    Glib::Mutex::Lock lock( m_loader_lock );
    bool ret = load_imgfile( LOADLEVEL_SIZEONLY );
    width = m_width;
    height = m_height;
    return ret;
}
