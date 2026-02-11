load_fs_info_cache()
{
	Glib::ustring output, error ;
	if ( blkid_found )
	{
		if ( ! Utils::execute_command( "blkid", output, error, true ) )
			fs_info_cache = output ;
		else
			fs_info_cache = "" ;
	}
}
