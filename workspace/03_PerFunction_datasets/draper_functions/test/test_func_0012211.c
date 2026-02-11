RP5H01_counter_r( int which ) {
	RP5H01	*chip;

	if ( which >= intf->num ) {
		logerror( "RP5H01_enable: trying to access an unmapped chip\n" );
		return 0;
	}


	chip = &RP5H01_state[which];


	if ( !chip->enabled )
		return 0;


	return ( chip->counter >> 5 ) & 1;
}
