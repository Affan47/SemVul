send_command(unsigned char *command, int command_length)
{
	int		retry = 0, sent;
	unsigned char	sbuf[128];


	sbuf[0] = PW_COMMAND_START_BYTE;
	sbuf[1] = (unsigned char)(command_length);
	memcpy(sbuf+2, command, command_length);
	command_length += 2;


	sbuf[command_length] = calc_checksum(sbuf);
	command_length += 1;

	upsdebug_hex (3, "send_command", sbuf, command_length);

	while (retry++ < PW_MAX_TRY) {

		if (retry == PW_MAX_TRY) {
			ser_send_char(upsfd, 0x1d);
			usleep(250000);
		}

		sent = ser_send_buf(upsfd, sbuf, command_length);

		if (sent == command_length) {
			return;
		}
	}
}
