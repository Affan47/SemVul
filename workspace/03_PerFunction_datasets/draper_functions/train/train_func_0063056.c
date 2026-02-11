_comedi_apply_calibration( comedi_t *dev, unsigned int subdev, unsigned int channel,
	unsigned int range, unsigned int aref, const char *cal_file_path )
{
	char file_path[ 1024 ];
	int retval;
	comedi_calibration_t *parsed_file;

	if( cal_file_path )
	{
		strncpy( file_path, cal_file_path, sizeof( file_path ) );
	}else
	{
		char *temp;

		temp = comedi_get_default_calibration_path( dev );
		if( temp == NULL ) return -1;
		strncpy( file_path, temp, sizeof( file_path ) );
		free( temp );
	}

	parsed_file = comedi_parse_calibration_file( file_path );
	if( parsed_file == NULL )
	{
		COMEDILIB_DEBUG( 3, "failed to parse calibration file\n" );
		return -1;
	}

	retval = comedi_apply_parsed_calibration( dev, subdev, channel, range, aref, parsed_file );

	comedi_cleanup_calibration( parsed_file );

	return retval;
}
