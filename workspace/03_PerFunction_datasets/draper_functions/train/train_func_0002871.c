slot_open_cache_browser()
{
    if( ! m_enable_menuslot ) return;
    if( ! m_img->is_cached() ) return;

    const std::string url = "file://" + m_img->get_cache_path();
    CORE::core_set_command( "open_url_browser", url );
}
