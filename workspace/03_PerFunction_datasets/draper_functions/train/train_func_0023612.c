save( Gtk::Window* parent, const std::string& path_to )
{
    if( ! is_cached() ) return false;

    std::string dir = MISC::get_dir( path_to );
    if( dir.empty() ) dir = SESSION::dir_img_save();

    std::string name = MISC::get_filename( path_to );
    if( name.empty() ) name = MISC::get_filename( m_url );

    std::string save_to = CACHE::copy_file( parent, get_cache_path(), dir + name, CACHE::FILE_TYPE_ALL );

    if( ! save_to.empty() ){
        SESSION::set_dir_img_save( MISC::get_dir( save_to ) );
        return true;
    }

    return false;
}
