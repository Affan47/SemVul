get_dmraid_dir_entries( const Glib::ustring & dev_path, std::vector<Glib::ustring> & dir_list )
{


	Glib::ustring dmraid_name = get_dmraid_name( dev_path ) ;


	Glib::ustring filename = "" ;
	Glib::Dir dir( DEV_MAP_PATH) ;
	while ( ( filename = dir .read_name() ) != "" )
	{
		if ( filename == "control" )
			continue ;

		if ( Utils::regexp_label( filename, "^(" + dmraid_name + ")" ) == dmraid_name )
			dir_list .push_back( filename ) ;
	}
}
