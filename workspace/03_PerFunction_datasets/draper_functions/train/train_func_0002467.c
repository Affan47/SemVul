upsdrv_shutdown(void)
{

	unsigned char answer[5], cbuf[3];

	int res, sec;


	if (getval("shutdown_delay") != NULL)
		bcmxcp_status.shutdowndelay = atoi(getval("shutdown_delay"));
	else
		bcmxcp_status.shutdowndelay = 120;


	send_write_command(AUTHOR, 4);

	sleep(PW_SLEEP);

	cbuf[0] = PW_LOAD_OFF_RESTART;
	cbuf[1] = (unsigned char)(bcmxcp_status.shutdowndelay & 0x00ff);
	cbuf[2] = (unsigned char)(bcmxcp_status.shutdowndelay >> 8);

	res = command_write_sequence(cbuf, 3, answer);
	if (res <= 0) {
		upslogx(LOG_ERR, "Short read from UPS");
		dstate_datastale();
		return;
	}

	sec = (256 * (unsigned char)answer[3]) + (unsigned char)answer[2];


	switch ((unsigned char) answer[0]) {

		case 0x31: {
			upsdrv_comm_good();
			upslogx(LOG_NOTICE,"Going down in %d sec", sec);
			break;
			}
		case 0x33: {
			fatalx(EXIT_FAILURE, "shutdown disabled by front panel");
			break;
			}
		case 0x36: {
			fatalx(EXIT_FAILURE, "Invalid parameter");
			break;
			}
		default: {
			fatalx(EXIT_FAILURE, "shutdown not supported");
			break;
			}
	}
}
