equal( const std::string& url )
{
    if( url.find( get_root() ) == 0 ){

        if( url.find( get_path_board() + "/" ) != std::string::npos ) return true;
        if( url.find( "BBS=" + get_id() ) != std::string::npos ) return true;
    }

    return false;
}
