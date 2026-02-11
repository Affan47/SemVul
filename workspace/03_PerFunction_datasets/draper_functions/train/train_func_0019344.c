set_calibration( comedi_t *dev, const comedi_calibration_t *parsed_file,
	unsigned int cal_index )
{
	int i, retval, num_caldacs;

	num_caldacs = parsed_file->settings[ cal_index ].num_caldacs;
	COMEDILIB_DEBUG( 4, "num_caldacs %i\n", num_caldacs );

	for( i = 0; i < num_caldacs; i++ )
	{
		comedi_caldac_t caldac;

		caldac = parsed_file->settings[ cal_index ].caldacs[ i ];
		COMEDILIB_DEBUG( 4, "subdev %i, ch %i, val %i\n", caldac.subdevice,
			caldac.channel,caldac.value);
		retval = comedi_data_write( dev, caldac.subdevice, caldac.channel,
			0, 0, caldac.value );
		if( retval < 0 ) return retval;
	}

	return 0;
}
