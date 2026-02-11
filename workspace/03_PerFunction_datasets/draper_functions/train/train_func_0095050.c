setvar (const char *varname, const char *val)
{
	unsigned char answer[128], cbuf[5];
	char namebuf[MAX_NUT_NAME_LENGTH];
	int res, sec, outlet_num;
	int onOff_setting = PW_AUTO_OFF_DELAY;

	upsdebugx(1, "entering setvar(%s, %s)", varname, val);

	strncpy(namebuf, varname, sizeof(namebuf));
	namebuf[NUT_OUTLET_POSITION] = 'n';

	if ( (strcasecmp(namebuf, "outlet.n.delay.start")) &&
		(strcasecmp(namebuf, "outlet.n.delay.shutdown")) ) {
			return STAT_SET_UNKNOWN;
	}

	if (outlet_block_len <= 8) {
		return STAT_SET_INVALID;
	}

	if (!strcasecmp(namebuf, "outlet.n.delay.start")) {
		onOff_setting = PW_AUTO_ON_DELAY;
	}

	send_write_command(AUTHOR, 4);
	sleep(PW_SLEEP);

	outlet_num = varname[NUT_OUTLET_POSITION] - '0';
	if (outlet_num < 1 || outlet_num > 9) {
		return STAT_SET_INVALID;
	}

	sec = atoi(val);


	if (sec < -1 || sec > 0x7FFF) {
		return STAT_SET_INVALID;
	}

	cbuf[0] = PW_SET_OUTLET_COMMAND;
	cbuf[1] = onOff_setting;
	cbuf[2] = outlet_num;
	cbuf[3] = sec&0xff;
	cbuf[4] = sec>>8;

	res = command_write_sequence(cbuf, 5, answer);
	if (res <= 0) {
		upslogx(LOG_ERR, "Short read from UPS");
		dstate_datastale();
		return -1;
	}

	switch ((unsigned char) answer[0]) {

		case 0x31: {
			upslogx(LOG_NOTICE,"Outlet %d %s delay set to %d sec",
				outlet_num, (onOff_setting == PW_AUTO_ON_DELAY)?"start":"shutdown", sec);
			dstate_setinfo(varname, "%d", sec);
			return STAT_SET_HANDLED;
			break;
			}
		case 0x33: {
			upslogx(LOG_NOTICE, "Set [%s] failed due to UPS busy", varname);

			return STAT_SET_UNKNOWN;
			break;
			}
		case 0x35: {
			upslogx(LOG_NOTICE, "Set [%s %s] failed due to parameter out of range", varname, val);
			return STAT_SET_UNKNOWN;
			break;
			}
		case 0x36: {
			upslogx(LOG_NOTICE, "Set [%s %s] failed due to invalid parameter", varname, val);
			return STAT_SET_UNKNOWN;
			break;
			}
		default: {
			upslogx(LOG_NOTICE, "Set [%s] not supported", varname);
			return STAT_SET_FAILED;
			break;
			}
	}

	return STAT_SET_INVALID;
}
