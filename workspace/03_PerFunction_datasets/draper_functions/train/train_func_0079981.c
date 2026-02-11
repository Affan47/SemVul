start_muxer(
	Serial* serial
	)
{
	LOG(LOG_INFO, "Configuring modem");
	char gsm_command[100];
	if (chat(serial->fd, "AT\r\n", 1) < 0)
	{
		LOG(LOG_WARNING, "Modem does not respond to AT commands, trying close mux mode");

			write_frame(0, NULL, 0, GSM0710_CONTROL_CLD | GSM0710_CR);

			write_frame(0, close_channel_cmd, 2, GSM0710_TYPE_UIH);
		SYSCHECK(chat(serial->fd, "AT\r\n", 1));
	}
	SYSCHECK(chat(serial->fd, "ATZ\r\n", 3));
	SYSCHECK(chat(serial->fd, "ATE0\r\n", 1));
	if (additional_functionality & AF_SIEMENS_C35)
	{
		SYSCHECK(snprintf(gsm_command, sizeof(gsm_command), "AT+IPR=%d\r\n", baud_rates[cmux_port_speed]));
		SYSCHECK(chat(serial->fd, gsm_command, 1));
		SYSCHECK(chat(serial->fd, "AT\r\n", 1));
		SYSCHECK(chat(serial->fd, "AT&S0\r\n", 1));
		SYSCHECK(chat(serial->fd, "AT\\Q3\r\n", 1));
	}
	if (pin_code >= 0)
	{
		LOG(LOG_DEBUG, "send pin %04d", pin_code);


		SYSCHECK(snprintf(gsm_command, sizeof(gsm_command), "AT+CPIN=%04d\r\n", pin_code));
		SYSCHECK(chat(serial->fd, gsm_command, 10));
	}
	if (additional_functionality & AF_SHORT_INIT)
		SYSCHECK(snprintf(gsm_command, sizeof(gsm_command), "AT+CMUX=1\r\n"));
	else
	{
		LOG(LOG_INFO, "Switching modem on");
		SYSCHECK(chat(serial->fd, "AT+CFUN=0\r\n", 10));
		SYSCHECK(snprintf(gsm_command, sizeof(gsm_command), "AT+CMUX=%d,%d,%d,%d"

			"\r\n"
			, cmux_mode
			, cmux_subset
			, cmux_port_speed
			, cmux_N1


			));
	}
	LOG(LOG_INFO, "Starting mux mode");
	SYSCHECK(chat(serial->fd, gsm_command, 3));
	muxer_trigger(1);
	serial->state = MUX_STATE_MUXING;
	LOG(LOG_INFO, "Waiting for mux-mode");
	sleep(1);
	LOG(LOG_INFO, "Init control channel");
	write_frame(0, NULL, 0, GSM0710_TYPE_SABM | GSM0710_PF);
	GIOChannel* channel = g_io_channel_unix_new(serial->fd);
	serial->g_source = g_io_add_watch(channel, G_IO_IN | G_IO_HUP, serial_device_read, serial);
	return 0;
}
