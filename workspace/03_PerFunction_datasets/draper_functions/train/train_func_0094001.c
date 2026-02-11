upsdrv_initups(void)
{
	struct termios tio;
	int baud = B1200;
	char *str;

	if ((str = getval("baudrate")) != NULL) {
		int temp = atoi(str);
		switch (temp) {
		case   300:
			baud =   B300; break;
		case   600:
			baud =   B600; break;
		case  1200:
			baud =  B1200; break;
		case  2400:
			baud =  B2400; break;
		case  4800:
			baud =  B4800; break;
		case  9600:
			baud =  B9600; break;
		case 19200:
			baud = B19200; break;
		case 38400:
			baud = B38400; break;
		default:
			fatalx(EXIT_FAILURE, "Unrecognized baudrate: %s", str);
		}
		upsdebugx(1, "baud_rate = %d", temp);
	}
	upsfd = ser_open(device_path);
	ser_set_speed(upsfd, device_path, baud);

	if (tcgetattr(upsfd, &tio) != 0)
		fatal_with_errno(EXIT_FAILURE, "tcgetattr(%s)", device_path);
	tio.c_lflag = ICANON;
	tio.c_iflag |= IGNCR;
	tio.c_cc[VMIN] = 0;
	tio.c_cc[VTIME] = 0;
	tcsetattr(upsfd, TCSANOW, &tio);

	if ((str = getval("input_timeout")) != NULL) {
		int temp = atoi(str);
		if (temp <= 0)
			fatalx(EXIT_FAILURE, "Bad input_timeout parameter: %s", str);
		input_timeout_sec = temp;
	}
	upsdebugx(1, "input_timeout = %d Sec", input_timeout_sec);

	if ((str = getval("output_pace")) != NULL) {
		int temp = atoi(str);
		if (temp <= 0)
			fatalx(EXIT_FAILURE, "Bad output_pace parameter: %s", str);
		output_pace_usec = temp;
	}
	upsdebugx(1, "output_pace = %d uSec", output_pace_usec);

	if ((str = getval("full_update_timer")) != NULL) {
		int temp = atoi(str);
		if (temp <= 0)
			fatalx(EXIT_FAILURE, "Bad full_update_timer parameter: %s", str);
		full_update_timer = temp;
	}
	upsdebugx(1, "full_update_timer = %d Sec", full_update_timer);

	use_crlf = testvar("use_crlf");
	upsdebugx(1, "use_crlf = %d", use_crlf);
	use_pre_lf = testvar("use_pre_lf");
	upsdebugx(1, "use_pre_lf = %d", use_pre_lf);
}
