register_int13_drive ( struct int13_drive *drive ) {
	uint8_t num_drives;


	guess_int13_geometry ( drive );


	get_real ( num_drives, BDA_SEG, BDA_NUM_DRIVES );
	drive->natural_drive = ( num_drives | 0x80 );


	if ( ( drive->drive & 0xff ) == 0xff ) {

		drive->drive = drive->natural_drive;
	} else {

		drive->drive |= 0x80;
	}

	DBG ( "Registered INT13 drive %02x (naturally %02x) with C/H/S "
	      "geometry %d/%d/%d\n", drive->drive, drive->natural_drive,
	      drive->cylinders, drive->heads, drive->sectors_per_track );


	if ( list_empty ( &drives ) )
		hook_int13();


	list_add ( &drive->list, &drives );


	int13_set_num_drives();
}
