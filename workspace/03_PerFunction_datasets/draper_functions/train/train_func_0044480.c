hd_init_winamp(Driver *drvthis)
{
	PrivateData *p = (PrivateData*) drvthis->private_data;
	HD44780_functions *hd44780_functions = p->hd44780_functions;


	if (p->numDisplays == 2) {
		if (p->have_backlight && (EnMask[1] == BL)) {
			report(RPT_ERR, "hd_init_winamp: backlight must be on different pin than 2nd controller");
			report(RPT_ERR, "hd_init_winamp: please change connection mapping in hd44780-winamp.c");
			return -1;
		}
		if (p->have_backlight && p->have_output) {
			report(RPT_ERR, "hd_init_winamp: backlight and output not possible with 2 controllers");
			return -1;
		}
	}
	else if (p->numDisplays == 3 && (p->have_backlight || p->have_output)) {
		report(RPT_ERR, "hd_init_winamp: backlight or output not possible with 3 controllers");
		return -1;
	}


	if (port_access_multiple(p->port,3)) {
		report(RPT_ERR, "%s: cannot get IO-permission for 0x%03X: %s",
				drvthis->name, p->port, strerror(errno));
		return -1;
	}

	hd44780_functions->senddata = lcdwinamp_HD44780_senddata;
	hd44780_functions->backlight = lcdwinamp_HD44780_backlight;
	hd44780_functions->readkeypad = lcdwinamp_HD44780_readkeypad;


	hd44780_functions->senddata(p, 0, RS_INSTR, FUNCSET | IF_8BIT);
	hd44780_functions->uPause(p, 4100);
	hd44780_functions->senddata(p, 0, RS_INSTR, FUNCSET | IF_8BIT);
	hd44780_functions->uPause(p, 100);

	common_init(p, IF_8BIT);

	if (p->have_keypad) {

		p->stuckinputs = lcdwinamp_HD44780_readkeypad(p, 0);
	}


	hd44780_functions->output = lcdwinamp_HD44780_output;

	return 0;
}
