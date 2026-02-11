get_post_log( const int num )
{
    std::string path = CACHE::path_postlog();

    if( num ) path += "-" + MISC::itostr( num );

    std::string html;
    CACHE::load_rawdata( path, html );
    return html;
}
