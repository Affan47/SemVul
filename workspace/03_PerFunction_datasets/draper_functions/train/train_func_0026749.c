upsdrv_initups(void)
{
	char buf[BUFFLEN];
	int RTS = TIOCM_RTS;

	upsfd = ser_open(device_path);
	ser_set_speed(upsfd, device_path, B2400);


	if (testvar ("oldmac"))
		RTS = ~TIOCM_RTS;


	ioctl(upsfd, TIOCMBIC, &RTS);
	enable_ups_comm();


	if (getval ("lowbatt"))
	{
		mge_ups.LowBatt = atoi (getval ("lowbatt"));

		mge_command(buf, sizeof(buf), "Bl %d",  mge_ups.LowBatt);
		if(!strcmp(buf, "OK"))
			upsdebugx(1, "Low Battery Level set to %d%%", mge_ups.LowBatt);
		else
			upsdebugx(1, "initups: Low Battery Level cannot be set");
	}


	if (getval ("ondelay"))
	{
		mge_ups.OnDelay = atoi (getval ("ondelay"));

		mge_command(buf, sizeof(buf), "Sm %d",  mge_ups.OnDelay);
		if(!strcmp(buf, "OK"))
			upsdebugx(1, "ON delay set to %d min", mge_ups.OnDelay);
		else
			upsdebugx(1, "initups: OnDelay unavailable");
	}


	if (getval ("offdelay"))
	{
		mge_ups.OffDelay = atoi (getval ("offdelay"));

		mge_command(buf, sizeof(buf), "Sn %d",  mge_ups.OffDelay);
		if(!strcmp(buf, "OK"))
			upsdebugx(1, "OFF delay set to %d sec", mge_ups.OffDelay);
		else
			upsdebugx(1, "initups: OffDelay unavailable");
	}
}
