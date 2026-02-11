riello_comm_setup(const char *port)
{
	BYTE length;

	upsdebugx(2, "set baudrate 9600");
	ser_set_speed(upsfd, device_path, B9600);

	upsdebugx(2, "try to detect SENTR");
	riello_init_serial();
	bufOut[0] = 192;
	ser_send_buf(upsfd, bufOut, 1);

	riello_serialcomm(&bufIn[0], DEV_RIELLOSENTRY);

	if (buf_ptr_length == 103) {
		typeRielloProtocol = DEV_RIELLOSENTRY;
		upslogx(LOG_INFO, "Connected to UPS SENTR on %s with baudrate %d", port, 9600);
		return;
	}

	upsdebugx(2, "try to detect GPSER");
	riello_init_serial();
	length = riello_prepare_gi(&bufOut[0]);

	ser_send_buf(upsfd, bufOut, length);

	riello_serialcomm(&bufIn[0], DEV_RIELLOGPSER);

	if (!wait_packet && !foundbadcrc && !foundnak) {
		typeRielloProtocol = DEV_RIELLOGPSER;
		upslogx(LOG_INFO, "Connected to UPS GPSER on %s with baudrate %d", port, 9600);
		return;
	}

	upsdebugx(2, "set baudrate 1200");
	ser_set_speed(upsfd, device_path, B1200);

	upsdebugx(2, "try to detect SENTR");
	riello_init_serial();
	bufOut[0] = 192;
	ser_send_buf(upsfd, bufOut, 1);

	riello_serialcomm(&bufIn[0], DEV_RIELLOSENTRY);

	if (buf_ptr_length == 103) {
		typeRielloProtocol = DEV_RIELLOSENTRY;
		upslogx(LOG_INFO, "Connected to UPS SENTR on %s with baudrate %d", port, 1200);
		return;
	}

	upsdebugx(2, "try to detect GPSER");
	riello_init_serial();
	length = riello_prepare_gi(&bufOut[0]);

	ser_send_buf(upsfd, bufOut, length);

	riello_serialcomm(&bufIn[0], DEV_RIELLOGPSER);

	if (!wait_packet && !foundbadcrc && !foundnak) {
		typeRielloProtocol = DEV_RIELLOGPSER;
		upslogx(LOG_INFO, "Connected to UPS GPSER on %s with baudrate %d", port, 1200);
		return;
	}

	fatalx(EXIT_FAILURE, "Can't connect to the UPS on port %s!\n", port);
}
