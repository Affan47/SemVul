kmc_get_shutter_speed(int fd)
{
	int fps, shutter_speed_number, shutter_speed_index,
				shutter_speed, i;
	char mode_wbuff[1], out;
	int pos=-1;

	mode_wbuff[0] = '\xA6';

	out = kmc_wr(fd, mode_wbuff);


	if(out == '\x00') shutter_speed_number = 1;
	if(out == '\x01') shutter_speed_number = 2;
	if(out == '\x02') shutter_speed_number = 3;
	if(out == '\x03') shutter_speed_number = 4;
	if(out == '\x04') shutter_speed_number = 5;
	if(out == '\x05') shutter_speed_number = 6;
	if(out == '\x06') shutter_speed_number = 7;


	fps =  kmc_get_record_rate(fd);


	for (i=0; i<N_RECORD_RATES ; i++) {
		if ( RECORD_RATES_MENU[i] == fps )
			pos=i;
		}
	shutter_speed_index = shutter_speed_number+pos-1;

	shutter_speed = SHUTTER_SPEEDS[shutter_speed_index];

	return shutter_speed;
}
