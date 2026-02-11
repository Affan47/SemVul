upsdrv_initups (void)
{
	upsdebugx(2, "entering upsdrv_initups()");


	upsfd = ser_open(device_path);
	ser_set_speed(upsfd, device_path, B2400);
	setline (1);


	if (getval ("lowbatt"))
		lowbatt = atoi (getval ("lowbatt"));


	if (getval ("ondelay"))
		ondelay = atoi (getval ("ondelay"));


	if (getval ("offdelay"))
		offdelay = atoi (getval ("offdelay"));


	if (getval ("notification"))
	  	notification = atoi (getval ("notification"));


	if (shut_ups_start () != 0)
		fatalx(EXIT_FAILURE, "No communication with UPS");
	else
		upsdebugx(2, "Communication with UPS established");


	if(hid_init_device() != 0)
		fatalx(EXIT_FAILURE, "Can't initialise HID device");
}
