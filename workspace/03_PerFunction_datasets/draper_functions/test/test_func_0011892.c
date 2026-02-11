insert_draft()
{
    const std::list< std::string > list_files = CACHE::open_load_diag( MESSAGE::get_admin()->get_win(),
                                                                       SESSION::get_dir_draft(), CACHE::FILE_TYPE_TEXT, false );

    if( list_files.size() )
    {
        const std::string open_path = *list_files.begin();
        std::string draft;

        SESSION::set_dir_draft( MISC::get_dir( open_path ) );
        CACHE::load_rawdata( open_path, draft );
        if( ! draft.empty() ) set_command( "add_message", draft );
    }
}
