get_filesystem_support()
{
	FS fs ;
	fs .filesystem = GParted::FS_NTFS ;

	if ( ! Glib::find_program_in_path( "ntfsresize" ) .empty() )
	{
		fs .read = GParted::FS::EXTERNAL ;
		fs .check = GParted::FS::EXTERNAL ;
	}

	if ( ! Glib::find_program_in_path( "ntfslabel" ) .empty() ) {
		Glib::ustring version ;

		fs .read_label = FS::EXTERNAL ;
		fs .write_label = FS::EXTERNAL ;


		Utils::execute_command( "ntfslabel --help ", output, error, false ) ;

		if ( ! ( version = Utils::regexp_label( output, "--new-serial[[:blank:]]" ) ) .empty() )
			fs .write_uuid = FS::EXTERNAL ;
	}

	if ( ! Glib::find_program_in_path( "mkntfs" ) .empty() )
	{
		fs .create = GParted::FS::EXTERNAL ;
		fs .create_with_label = GParted::FS::EXTERNAL ;
	}


	if ( fs .read && fs .check )
	{
		fs .grow = GParted::FS::EXTERNAL ;

		if ( fs .read )
			fs .shrink = GParted::FS::EXTERNAL ;
	}


	if ( ! Glib::find_program_in_path( "ntfsclone" ) .empty() )
		fs .copy = GParted::FS::EXTERNAL ;

	if ( fs .check )
		fs .move = GParted::FS::GPARTED ;

	fs .online_read = FS::GPARTED ;


	fs. MIN = 2 * MEBIBYTE;

	return fs ;
}
