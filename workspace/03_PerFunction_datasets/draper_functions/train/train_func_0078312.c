make_path_dmraid_compatible( Glib::ustring partition_path )
{


	Glib::ustring reg_exp ;
	Glib::ustring partition_number ;

	for ( unsigned int k=0; k < dmraid_devices .size(); k++ )
	{
		reg_exp = DEV_MAP_PATH + dmraid_devices[ k ] + "p([0-9]+)" ;
		partition_number = Utils::regexp_label( partition_path, reg_exp ) ;
		if ( ! partition_number .empty() )
		{
			partition_path = DEV_MAP_PATH + dmraid_devices[ k ] + partition_number ;
			return partition_path ;
		}
	}


	reg_exp = "/dev/dm-[0-9]+p([0-9]+)" ;
	partition_number = Utils::regexp_label( partition_path, reg_exp ) ;
	if ( ! partition_number .empty() )
	{
		reg_exp = "(/dev/dm-[0-9]+)p[0-9]+" ;
		Glib::ustring device_path = Utils::regexp_label( partition_path, reg_exp ) ;
		if ( ! device_path .empty() )
		{
			device_path = get_udev_dm_name( device_path ) ;
			partition_path = DEV_MAP_PATH + device_path + partition_number ;
		}
	}

	return partition_path ;
}
