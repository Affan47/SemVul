equal( const std::string& url )
{
    if( url.find( get_root() ) == 0
        && url.find( get_path_board() + "/" ) != std::string::npos ) return true;

    return false;
}
