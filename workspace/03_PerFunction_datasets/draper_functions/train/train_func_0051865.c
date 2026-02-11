upsdrv_initinfo(void)
{
	if (!upsc_commandlist()) {
		upslogx(LOG_ERR, "No contact with UPS, delaying init.");
		status = UPSC_STAT_NOTINIT;
		return;
	} else {
		status = 0;
	}

	upsc_getbaseinfo();
	if (can_upda) {
		upsc_flush_input();
		upscsend("UPDA");
	}
	if (can_upid) {
		upsc_getvalue("UPID", NULL, "ACID", "ups.id", NULL);
	}
	if (can_uppm) {
		check_uppm();
	}


	setvar("ups.delay.shutdown", "10");
	setvar("ups.delay.reboot", "60");

	upsh.instcmd = instcmd;
	upsh.setvar = setvar;
}
